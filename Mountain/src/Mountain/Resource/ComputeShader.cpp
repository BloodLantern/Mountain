#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Resource/ComputeShader.hpp"

#include <glad/glad.h>

#include "Mountain/Resource/ResourceManager.hpp"

using namespace Mountain;

bool ComputeShader::SetSourceData(const Pointer<File>& shader)
{
    m_File = shader;

    if (!Load(shader->GetData(), shader->GetSize()))
    {
        m_File = nullptr;
        return false;
    }

    m_SourceDataSet = true;

    return true;
}

bool ComputeShader::Load(const c8* const buffer, const s64 length)
{
    m_Code = Utils::RemoveByteOrderMark(std::string{buffer, static_cast<usize>(length)});
    ReplaceIncludes(m_Code, m_File->GetPath(), m_DependentShaderFiles);

    m_SourceDataSet = true;

    return true;
}

void ComputeShader::Load()
{
    const u32 id = glCreateShader(GL_COMPUTE_SHADER);
#ifdef _DEBUG
    std::string name = m_Name;
    const std::string& fileName = m_File ? m_File->GetName() : name;
    glObjectLabel(GL_SHADER, id, static_cast<GLsizei>(fileName.length()), fileName.c_str());
#endif

    const c8* data = m_Code.c_str();
    const s32 dataLength = static_cast<s32>(m_Code.size());
    glShaderSource(id, 1, &data, &dataLength);

    glCompileShader(id);
    if (CheckCompileError(id))
    {
        Logger::LogWarning("Compute shader load canceled because of compilation errors");
        return;
    }

    if (glIsProgram(m_Id))
        glDeleteProgram(m_Id);

    m_Id = glCreateProgram();
#ifdef _DEBUG
    name = name.substr(0, name.find_last_of('.')); // Remove file extension
    glObjectLabel(GL_PROGRAM, m_Id, static_cast<GLsizei>(name.length()), name.c_str());
#endif

	glAttachShader(m_Id, id);
    glLinkProgram(m_Id);

    if (glIsShader(id))
    {
        glDetachShader(m_Id, id);
        glDeleteShader(id);
    }

    static_cast<void>(CheckLinkError());

    m_Loaded = true;
}

void ComputeShader::Unload()
{
	glDeleteProgram(m_Id);

    m_DependentShaderFiles.clear();
    m_Id = 0;
    m_Loaded = false;
}

void ComputeShader::ResetSourceData()
{
    m_Code.clear();
}

bool ComputeShader::Reload(const bool reloadInBackend)
{
    m_DependentShaderFiles.clear();

    const bool result = SetSourceData(m_File);

    if (reloadInBackend)
        Load();

    return result;
}

void ComputeShader::Dispatch(const u32 groupsX, const u32 groupsY, const u32 groupsZ) const
{
    if (groupsX == 0 || groupsY == 0 || groupsZ == 0)
        THROW(ArgumentException{"ComputeShader::Dispatch needs all dimension arguments to be at least 1"});

    glUseProgram(m_Id);
    glDispatchCompute(groupsX, groupsY, groupsZ);
    glUseProgram(0);
}

bool ComputeShader::CheckCompileError(const u32 id) const
{
    return ShaderBase::CheckCompileError(id, "Compute", m_Code);
}
