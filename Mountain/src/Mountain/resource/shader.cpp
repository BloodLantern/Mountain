#include "Mountain/resource/shader.hpp"

#include <glad/glad.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/resource/resource_manager.hpp"
#include "Mountain/utils/logger.hpp"

using namespace Mountain;

Graphics::ShaderType Shader::FileExtensionToType(const std::string& extension)
{
    if (std::ranges::find(VertexFileExtensions, extension) != VertexFileExtensions.end())
        return Graphics::ShaderType::Vertex;

    if (std::ranges::find(FragmentFileExtensions, extension) != FragmentFileExtensions.end())
        return Graphics::ShaderType::Fragment;

    Logger::LogError("Invalid file extension for shader : {}", extension);
    throw std::invalid_argument("Invalid file extension for shader");
}

bool_t Shader::SetSourceData(const Pointer<File>& shader)
{
    const Graphics::ShaderType type = FileExtensionToType(shader->GetExtension());

    if (!Load(shader->GetData(), shader->GetSize(), type))
        return false;

    m_Files[static_cast<size_t>(type)] = shader;

    m_SourceDataSet = true;

    return true;
}

bool_t Shader::Load(const char_t* const buffer, const int64_t length, const Graphics::ShaderType type)
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
#ifdef _DEBUG
    const std::string name = m_Name.substr(ResourceManager::ReservedShaderPrefix.length());
    glObjectLabel(GL_PROGRAM, m_Id, static_cast<GLsizei>(name.length()), name.c_str());
#endif

    std::array<uint32_t, Graphics::ShaderTypeCount> shaderIds;
    for (size_t i = 0; i < Graphics::ShaderTypeCount; i++)
    {
        const ShaderCode& code = m_Code[i];
        if (code.code.empty())
            continue;

        uint32_t& id = shaderIds[i];
        id = glCreateShader(ShaderTypeToOpenGl(code.type));
#ifdef _DEBUG
        const Pointer file = m_Files[i];
        const std::string& fileName = file ? file->GetName() : name + '/' + magic_enum::enum_name(code.type).data();
        glObjectLabel(GL_SHADER, id, static_cast<GLsizei>(fileName.length()), fileName.c_str());
#endif

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
        {
            glDetachShader(m_Id, shaderId);
            glDeleteShader(shaderId);
        }
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

bool_t Shader::Reload(const bool_t reloadInBackend)
{
    if (reloadInBackend)
        Unload();

    const bool_t result = SetSourceData(m_Files[0]) && SetSourceData(m_Files[1]);

    if (reloadInBackend)
        Load();

    return result;
}

bool_t Shader::Reload(const Pointer<File>& file, const bool_t reloadInBackend) { return Resource::Reload(file, reloadInBackend); }

std::array<Pointer<File>, Graphics::ShaderTypeCount>& Shader::GetFiles() { return m_Files; }

const std::array<Pointer<File>, Graphics::ShaderTypeCount>& Shader::GetFiles() const { return m_Files; }

std::array<ShaderCode, Graphics::ShaderTypeCount>& Shader::GetCode() { return m_Code; }

const std::array<ShaderCode, Graphics::ShaderTypeCount>& Shader::GetCode() const { return m_Code; }

void Shader::Use() const { glUseProgram(m_Id); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Shader::Unuse() const { glUseProgram(0); }

void Shader::CheckCompilationError(const uint32_t id, const Graphics::ShaderType type)
{
    int success = 0;
    
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint infoLogSize = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::vector<char_t> infoLog(static_cast<size_t>(infoLogSize));
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while compiling shader '{}' of type '{}': {}", m_Name, magic_enum::enum_name(type), infoLog.data());
    }
}
