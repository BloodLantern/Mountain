#include "Mountain/resource/shader_base.hpp"

#include <glad/glad.h>

#include <Maths/math.hpp>

#include "Mountain/utils/logger.hpp"

using namespace Mountain;

void ShaderBase::SetUniform(const std::string_view keyName, const int32_t value) const { glProgramUniform1i(m_Id, GetUniformLocation(keyName), value); }

void ShaderBase::SetUniform(const std::string_view keyName, const bool_t value) const { SetUniform(keyName, static_cast<int32_t>(value)); }

void ShaderBase::SetUniform(const std::string_view keyName, const float_t value) const { glProgramUniform1f(m_Id, GetUniformLocation(keyName), value); }

void ShaderBase::SetUniform(const std::string_view keyName, const Vector2& value) const
{
    glProgramUniform2fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ShaderBase::SetUniform(const std::string_view keyName, const Vector3& value) const
{
    glProgramUniform3fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ShaderBase::SetUniform(const std::string_view keyName, const Vector4& value) const
{
    glProgramUniform4fv(m_Id, GetUniformLocation(keyName), 1, value.Data());
}

void ShaderBase::SetUniform(const std::string_view keyName, const Color& value) const { SetUniform(keyName, static_cast<Vector4>(value)); }

void ShaderBase::SetUniform(const std::string_view keyName, const Matrix2& value) const
{
    glProgramUniformMatrix2fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

void ShaderBase::SetUniform(const std::string_view keyName, const Matrix3& value) const
{
    glProgramUniformMatrix3fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

void ShaderBase::SetUniform(const std::string_view keyName, const Matrix& value) const
{
    glProgramUniformMatrix4fv(m_Id, GetUniformLocation(keyName), 1, GL_FALSE, value.Data());
}

uint32_t ShaderBase::GetId() const { return m_Id; }

void ShaderBase::CheckLinkError()
{
    int success = 0;

    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint infoLogSize = 0;
        glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::vector<char_t> infoLog(static_cast<size_t>(infoLogSize));
        glGetProgramInfoLog(m_Id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while linking shader program '{}': {}", m_Name, infoLog.data());
    }
}

int32_t ShaderBase::GetUniformLocation(const std::string_view keyName) const { return glGetUniformLocation(m_Id, keyName.data()); }
