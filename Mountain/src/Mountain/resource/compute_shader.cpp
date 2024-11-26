#include "Mountain/resource/compute_shader.hpp"

#include <glad/glad.h>

#include "Mountain/resource/resource_manager.hpp"

using namespace Mountain;

bool_t ComputeShader::SetSourceData(const Pointer<File>& shader)
{
    if (!Load(shader->GetData(), shader->GetSize()))
        return false;

    m_File = shader;

    m_SourceDataSet = true;

    return true;
}

bool_t ComputeShader::Load(const char_t* const buffer, const int64_t length)
{
    m_Code = std::string{ buffer, static_cast<size_t>(length) };

    m_SourceDataSet = true;

    return true;
}

void ComputeShader::Load()
{
    m_Id = glCreateProgram();
#ifdef _DEBUG
    const std::string name = m_Name.substr(ResourceManager::ReservedComputeShaderPrefix.length());
    glObjectLabel(GL_PROGRAM, m_Id, static_cast<GLsizei>(name.length()), name.c_str());
#endif

    const uint32_t id = glCreateShader(GL_COMPUTE_SHADER);
#ifdef _DEBUG
    const std::string& fileName = m_File ? m_File->GetName() : name + "/Compute";
    glObjectLabel(GL_SHADER, id, static_cast<GLsizei>(fileName.length()), fileName.c_str());
#endif

    const char_t* data = m_Code.c_str();
    const int32_t dataLength = static_cast<int32_t>(m_Code.size());
    glShaderSource(id, 1, &data, &dataLength);

    glCompileShader(id);
	CheckCompilationError(id);

	glAttachShader(m_Id, id);
    glLinkProgram(m_Id);

    if (glIsShader(id))
        glDeleteShader(id);

    CheckLinkError();

    m_Loaded = true;
}

void ComputeShader::Unload()
{
	glDeleteProgram(m_Id);

    m_Id = 0;
    m_Loaded = false;
}

void ComputeShader::ResetSourceData()
{
    m_Code.clear();
}

void ComputeShader::SetUniform(const std::string_view keyName, const int32_t value) const { glProgramUniform1i(m_Id, GetUniformLocation(keyName), value); }

void ComputeShader::SetUniform(const std::string_view keyName, const bool_t value) const { SetUniform(keyName, static_cast<int32_t>(value)); }

void ComputeShader::SetUniform(const std::string_view keyName, const float_t value) const { glProgramUniform1f(m_Id, GetUniformLocation(keyName), value); }

void ComputeShader::SetUniform(const std::string_view keyName, const Vector2& value) const
{
    glProgramUniform2fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ComputeShader::SetUniform(const std::string_view keyName, const Vector3& value) const
{
    glProgramUniform3fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ComputeShader::SetUniform(const std::string_view keyName, const Vector4& value) const
{
    glProgramUniform4fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ComputeShader::SetUniform(const std::string_view keyName, const Color& value) const { SetUniform(keyName, static_cast<Vector4>(value)); }

void ComputeShader::SetUniform(const std::string_view keyName, const Matrix2& value) const
{
    glProgramUniformMatrix2fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

void ComputeShader::SetUniform(const std::string_view keyName, const Matrix3& value) const
{
    glProgramUniformMatrix3fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

void ComputeShader::SetUniform(const std::string_view keyName, const Matrix& value) const
{
    glProgramUniformMatrix4fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

uint32_t ComputeShader::GetId() const { return m_Id; }

void ComputeShader::Use() const { glUseProgram(m_Id); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void ComputeShader::Unuse() const { glUseProgram(0); }

void ComputeShader::CheckCompilationError(const uint32_t id)
{
    int success = 0;
    constexpr uint32_t infoLogSize = 1024;
    std::vector<char_t> infoLog(infoLogSize);

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while compiling shader '{}' of type 'Compute': {}", m_Name, infoLog.data());
    }
}

void ComputeShader::CheckLinkError()
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

int32_t ComputeShader::GetUniformLocation(const std::string_view keyName) const { return glGetUniformLocation(m_Id, keyName.data()); }