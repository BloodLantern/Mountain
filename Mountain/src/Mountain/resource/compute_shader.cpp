#include "Mountain/resource/compute_shader.hpp"

#include <glad/glad.h>

#include "Mountain/resource/resource_manager.hpp"

using namespace Mountain;

bool_t ComputeShader::SetSourceData(const Pointer<File>& shader)
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

bool_t ComputeShader::Load(const char_t* const buffer, const int64_t length)
{
    m_Code = std::string{ buffer, static_cast<size_t>(length) };
    ReplaceIncludes(m_Code);

    m_SourceDataSet = true;

    return true;
}

void ComputeShader::Load()
{
    m_Id = glCreateProgram();
#ifdef _DEBUG
    std::string name = m_Name;
    name = name.substr(0, name.find_last_of('.')); // Remove file extension
    glObjectLabel(GL_PROGRAM, m_Id, static_cast<GLsizei>(name.length()), name.c_str());
#endif

    const uint32_t id = glCreateShader(GL_COMPUTE_SHADER);
#ifdef _DEBUG
    const std::string& fileName = m_File ? m_File->GetName() : name;
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
    {
        glDetachShader(m_Id, id);
        glDeleteShader(id);
    }

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

void ComputeShader::Dispatch(const uint32_t groupsX, const uint32_t groupsY, const uint32_t groupsZ) const
{
    if (groupsX == 0 || groupsY == 0 || groupsZ == 0)
        throw std::invalid_argument{ "ComputeShader::Dispatch needs all dimension arguments to be at least 1" };

    glUseProgram(m_Id);
    glDispatchCompute(groupsX, groupsY, groupsZ);
    glUseProgram(0);
}

void ComputeShader::CheckCompilationError(const uint32_t id)
{
    int success = 0;

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint infoLogSize = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::vector<char_t> infoLog(static_cast<size_t>(infoLogSize));
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while compiling compute shader '{}': {}", m_Name, infoLog.data());
    }
}
