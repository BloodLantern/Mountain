#include "Mountain/Resource/Shader.hpp"

#include <glad/glad.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

Graphics::ShaderType Shader::FileExtensionToType(const std::string& extension)
{
    if (std::ranges::find(VertexFileExtensions, extension) != VertexFileExtensions.end())
        return Graphics::ShaderType::Vertex;

    if (std::ranges::find(FragmentFileExtensions, extension) != FragmentFileExtensions.end())
        return Graphics::ShaderType::Fragment;

    Logger::LogError("Invalid file extension for shader : {}", extension);
    THROW(ArgumentException{"Invalid file extension for shader", "extension"});
}

bool_t Shader::SetSourceData(const Pointer<File>& shader)
{
    const Graphics::ShaderType type = FileExtensionToType(shader->GetExtension());

    m_File = shader;
    const bool_t loadResult = Load(shader->GetData(), shader->GetSize(), type);
    m_File = nullptr;

    if (!loadResult)
        return false;

    m_Files[static_cast<size_t>(type)] = shader;

    m_SourceDataSet = true;

    return true;
}

bool_t Shader::Load(const char_t* const buffer, const int64_t length, const Graphics::ShaderType type)
{
    ShaderCode& code = m_Code[static_cast<size_t>(type)];
    code.code = std::string(buffer, length);
    ReplaceIncludes(code.code, m_File->GetPath(), dependentShaderFiles);
    code.type = type;

    m_SourceDataSet = true;

    return true;
}

void Shader::Load()
{
    std::array<uint32_t, magic_enum::enum_count<Graphics::ShaderType>()> shaderIds;
    bool_t compileError = false;
    for (size_t i = 0; i < magic_enum::enum_count<Graphics::ShaderType>(); i++)
    {
        const ShaderCode& code = m_Code[i];
        if (code.code.empty())
            continue;

        uint32_t& id = shaderIds[i];
        id = glCreateShader(ToOpenGl(code.type));
#ifdef _DEBUG
        const Pointer file = m_Files[i];
        const std::string& fileName = file ? file->GetName() : m_Name + '/' + magic_enum::enum_name(code.type).data();
        glObjectLabel(GL_SHADER, id, static_cast<GLsizei>(fileName.length()), fileName.c_str());
#endif

        const char_t* data = code.code.c_str();
        int32_t dataLength = static_cast<int32_t>(code.code.size());
        glShaderSource(id, 1, &data, &dataLength);

        glCompileShader(id);
		if (CheckCompileError(shaderIds[i], code.type))
		    compileError = true;
    }

    if (compileError)
    {
        Logger::LogWarning("Shader load canceled because of compilation errors");
        return;
    }

    if (glIsProgram(m_Id))
        glDeleteProgram(m_Id);

    m_Id = glCreateProgram();
#ifdef _DEBUG
    glObjectLabel(GL_PROGRAM, m_Id, static_cast<GLsizei>(m_Name.length()), m_Name.c_str());
#endif

    for (size_t i = 0; i < magic_enum::enum_count<Graphics::ShaderType>(); i++)
		glAttachShader(m_Id, shaderIds[i]);

    glLinkProgram(m_Id);

    for (const uint32_t shaderId : shaderIds)
    {
        if (glIsShader(shaderId))
        {
            glDetachShader(m_Id, shaderId);
            glDeleteShader(shaderId);
        }
    }

    if (CheckLinkError())
        THROW(RuntimeError{"A Shader failed to link after compiling successfully"});

    m_Loaded = true;
}

void Shader::Unload()
{
	glDeleteProgram(m_Id);

    dependentShaderFiles.clear();
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
    dependentShaderFiles.clear();

    const bool_t result = SetSourceData(m_Files[0]) && SetSourceData(m_Files[1]);

    if (reloadInBackend)
        Load();

    return result;
}

bool_t Shader::Reload(const Pointer<File>& file, const bool_t reloadInBackend) { return Resource::Reload(file, reloadInBackend); }

std::array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetFiles() { return m_Files; }

const std::array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetFiles() const { return m_Files; }

std::array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetCode() { return m_Code; }

const std::array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetCode() const { return m_Code; }

void Shader::Use() const { glUseProgram(m_Id); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Shader::Unuse() const { glUseProgram(0); }

bool_t Shader::CheckCompileError(const uint32_t id, const Graphics::ShaderType type) const
{
    return ShaderBase::CheckCompileError(id, magic_enum::enum_name(type), m_Code[static_cast<size_t>(type)].code);
}
