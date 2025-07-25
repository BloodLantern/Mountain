#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Resource/Shader.hpp"

#include <glad/glad.h>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

Graphics::ShaderType Shader::FileExtensionToType(const std::string& extension)
{
    if (Contains(VertexFileExtensions, extension))
        return Graphics::ShaderType::Vertex;

    if (Contains(FragmentFileExtensions, extension))
        return Graphics::ShaderType::Fragment;

    if (Contains(GeometryFileExtensions, extension))
        return Graphics::ShaderType::Geometry;

    THROW(ArgumentException{"Invalid file extension for shader", TO_STRING(extension)});
}

bool_t Shader::SetSourceData(const Pointer<File>& file)
{
    const Graphics::ShaderType type = FileExtensionToType(file->GetExtension());

    m_File = file;
    const bool_t loadResult = Load(file->GetData(), file->GetSize(), type);
    m_File = nullptr;

    if (!loadResult)
        return false;

    m_Files[static_cast<size_t>(type)] = file;

    m_SourceDataSet = true;

    return true;
}

bool_t Shader::Load(const char_t* const buffer, const int64_t length, const Graphics::ShaderType type)
{
    ShaderCode& code = m_Code[static_cast<size_t>(type)];
    code.code = Utils::RemoveByteOrderMark(std::string{buffer, static_cast<size_t>(length)});
    ReplaceIncludes(code.code, m_File->GetPath(), dependentShaderFiles);
    code.type = type;

    m_SourceDataSet = true;

    return true;
}

void Shader::Load()
{
    Array<uint32_t, magic_enum::enum_count<Graphics::ShaderType>()> shaderIds{0};
    bool_t compileError = false;
    for (size_t i = 0; i < shaderIds.GetSize(); i++)
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

    for (size_t i = 0; i < shaderIds.GetSize(); i++)
    {
        if (shaderIds[i] != 0)
            glAttachShader(m_Id, shaderIds[i]);
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

    if (CheckLinkError())
        THROW(InvalidOperationException{"A Shader failed to link after compiling successfully"});

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
    m_Files.Fill(nullptr);
    m_Code.Fill({});
}

bool_t Shader::Reload(const bool_t reloadInBackend)
{
    dependentShaderFiles.clear();

    if (!m_Files.All([&](const Pointer<File>& file) { return !file || SetSourceData(file); }))
        return false;

    if (reloadInBackend)
        Load();

    return true;
}

bool_t Shader::Reload(const Pointer<File>& file, const bool_t reloadInBackend) { return Resource::Reload(file, reloadInBackend); }

Array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetFiles() { return m_Files; }

const Array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetFiles() const { return m_Files; }

Array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetCode() { return m_Code; }

const Array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& Shader::GetCode() const { return m_Code; }

void Shader::Use() const { glUseProgram(m_Id); }

// ReSharper disable once CppMemberFunctionMayBeStatic
void Shader::Unuse() const { glUseProgram(0); }

bool_t Shader::CheckCompileError(const uint32_t id, const Graphics::ShaderType type) const
{
    return ShaderBase::CheckCompileError(id, magic_enum::enum_name(type), m_Code[static_cast<size_t>(type)].code);
}
