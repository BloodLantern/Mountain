#include "Mountain/resource/shader.hpp"

#include <glad/glad.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/utils/logger.hpp"

using namespace Mountain;

ShaderType Shader::FileExtensionToType(const std::string& extension)
{
    if (std::ranges::find(VertexFileExtensions, extension) != VertexFileExtensions.end())
        return ShaderType::Vertex;

    if (std::ranges::find(FragmentFileExtensions, extension) != FragmentFileExtensions.end())
        return ShaderType::Fragment;

    Logger::LogError("Invalid file extension for shader : {}", extension);
    throw std::invalid_argument("Invalid file extension for shader");
}

bool_t Shader::SetSourceData(const Pointer<File>& shader)
{
    const ShaderType type = FileExtensionToType(shader->GetExtension());

    if (!Load(shader->GetData(), shader->GetSize(), type))
        return false;

    m_Files[static_cast<size_t>(type)] = shader;
    
    m_SourceDataSet = true;
    
    return true;
}

bool_t Shader::Load(const char_t* const buffer, const int64_t length, const ShaderType type)
{
    ShaderCode& code = m_Code[static_cast<size_t>(type)];
    code.code = std::string(buffer, length);
    code.type = type;
    
    m_SourceDataSet = true;
    
    return true;
}

void Shader::Load()
{
    m_Id = glCreateProgram();

    std::array<uint32_t, ShaderTypeCount> shaderIds;
    for (size_t i = 0; i < ShaderTypeCount; i++)
    {
        const ShaderCode& code = m_Code[i];
        if (code.code.empty())
            continue;

        uint32_t& id = shaderIds[i];
        id = glCreateShader(ShaderTypeToOpenGl(code.type));
        
        const char_t* data = code.code.c_str();
        int32_t dataLength = static_cast<int32_t>(code.code.size());
        glShaderSource(id, 1, &data, &dataLength);
        
        glCompileShader(id);
		CheckCompilationError(shaderIds[i], code.type);
        
		glAttachShader(m_Id, id);
    }
    glLinkProgram(m_Id);

    for (const uint32_t shaderId : shaderIds)
    {
        if (glIsShader(shaderId))
            glDeleteShader(shaderId);
    }

    CheckLinkError();
    
    m_Loaded = true;
}

void Shader::Unload()
{
	glDeleteProgram(m_Id);
    
    m_Id = 0;
    m_Loaded = false;
}

void Shader::ResetSourceData()
{
    m_Files.fill(nullptr);
    m_Code.fill({});
}

void Shader::SetUniform(const std::string_view& keyName, const int32_t value) const { glUniform1i(GetUniformLocation(keyName.data()), value); }

void Shader::SetUniform(const std::string_view& keyName, const bool_t value) const { SetUniform(keyName, static_cast<int32_t>(value)); }

void Shader::SetUniform(const std::string_view& keyName, const float_t value) const { glUniform1f(GetUniformLocation(keyName.data()), value); }

void Shader::SetUniform(const std::string_view& keyName, const Vector2& value) const { glUniform2fv(GetUniformLocation(keyName.data()), 1, value.Raw()); }

void Shader::SetUniform(const std::string_view& keyName, const Vector3& value) const { glUniform3fv(GetUniformLocation(keyName.data()), 1, value.Raw()); }

void Shader::SetUniform(const std::string_view& keyName, const Vector4& value) const { glUniform4fv(GetUniformLocation(keyName.data()), 1, value.Raw()); }

void Shader::SetUniform(const std::string_view& keyName, const Color& value) const { SetUniform(keyName, static_cast<Vector4>(value)); }

void Shader::SetUniform(const std::string_view& keyName, const Matrix2& value) const { glUniformMatrix2fv(GetUniformLocation(keyName.data()), 1, GL_FALSE, value.Raw()); }

void Shader::SetUniform(const std::string_view& keyName, const Matrix3& value) const { glUniformMatrix3fv(GetUniformLocation(keyName.data()), 1, GL_FALSE, value.Raw()); }

void Shader::SetUniform(const std::string_view& keyName, const Matrix& value) const { glUniformMatrix4fv(GetUniformLocation(keyName.data()), 1, GL_FALSE, value.Raw()); }

uint32_t Shader::GetId() const { return m_Id; }

void Shader::Use() const { glUseProgram(m_Id); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Shader::Unuse() const { glUseProgram(0); }

uint32_t Shader::ShaderTypeToOpenGl(const ShaderType shaderType)
{
    switch (shaderType)
    {
        case ShaderType::Vertex:
            return GL_VERTEX_SHADER;
			
        case ShaderType::Fragment:
            return GL_FRAGMENT_SHADER;

        case ShaderType::Count:
            break;
    }
    
    throw std::invalid_argument("Invalid shader type");
}

void Shader::CheckCompilationError(const uint32_t id, const ShaderType type)
{
    int success = 0;
    constexpr uint32_t infoLogSize = 1024;
    std::vector<char_t> infoLog(infoLogSize);
    
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while compiling shader '{}': {}", m_Files[static_cast<size_t>(type)]->GetName(), infoLog.data());
    }
}

void Shader::CheckLinkError()
{
    int success = 0;
    constexpr uint32_t infoLogSize = 1024;
    std::vector<char_t> infoLog(infoLogSize);
    
    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_Id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while linking shader program '{}': {}", m_Name, infoLog.data());
    }
}

int32_t Shader::GetUniformLocation(const std::string_view& keyName) const { return glGetUniformLocation(m_Id, keyName.data()); }
