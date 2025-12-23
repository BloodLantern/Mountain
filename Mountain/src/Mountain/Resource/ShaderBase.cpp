#include "Mountain/Resource/ShaderBase.hpp"

#include <glad/glad.h>

#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Graphics/Graphics.hpp"
#include "Mountain/Math/Math.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

void ShaderBase::Unload()
{
    Resource::Unload();

    m_UniformLocationCache.clear();
}

void ShaderBase::SetUniform(const c8* uniformName, const s32 value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const u32 value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const bool value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const f32 value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Vector2i value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Vector2 value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Vector3& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Vector4& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Color& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Matrix2& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Matrix3& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

void ShaderBase::SetUniform(const c8* uniformName, const Matrix& value) const { Graphics::SetProgramUniform(m_Id, GetUniformLocation(uniformName), value); }

bool ShaderBase::CheckCompileError(const u32 id, const std::string_view type, const std::string& code) const
{
    int success = 0;

    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint infoLogSize = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::string infoLog(static_cast<usize>(infoLogSize), '\0');
        glGetShaderInfoLog(id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while compiling shader '{}' of type '{}': {}", m_Name, type, Utils::Trim(infoLog).data());

        std::istringstream input{ infoLog };
        std::vector<std::pair<usize, std::string>> relatedLines;
        usize pos = infoLog.find("0(");
        while (pos != std::string::npos)
        {
            const usize endPos = infoLog.find(')', pos);

            const usize lineIndex = std::stoull(infoLog.substr(pos + 2, endPos - pos));
            relatedLines.emplace_back(lineIndex, Utils::Trim(Utils::GetLine(code, lineIndex - 1)));

            pos = infoLog.find("0(", endPos);
        }

        if (!relatedLines.empty())
        {
            Logger::LogError("Found potentially related code lines:");
            for (const auto& line : relatedLines)
                Logger::LogError("Line {}: {}", line.first, line.second);
        }

        return true;
    }

    return false;
}

bool ShaderBase::CheckLinkError() const
{
    int success = 0;

    glGetProgramiv(m_Id, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint infoLogSize = 0;
        glGetProgramiv(m_Id, GL_INFO_LOG_LENGTH, &infoLogSize);
        std::string infoLog(static_cast<usize>(infoLogSize), '\0');
        glGetProgramInfoLog(m_Id, infoLogSize, nullptr, infoLog.data());
        Logger::LogError("Error while linking shader program '{}': {}", m_Name, Utils::Trim(infoLog).data());

        return true;
    }

    return false;
}

s32 ShaderBase::GetUniformLocation(const c8* uniformName) const
{
    if (m_UniformLocationCache.contains(uniformName))
        return m_UniformLocationCache[uniformName];

    const s32 result = Graphics::GetProgramUniformLocation(m_Id, uniformName);
    m_UniformLocationCache[uniformName] = result;
    return result;
}

void ShaderBase::ReplaceIncludes(std::string& code, const std::filesystem::path& path, std::unordered_set<std::filesystem::path>& replacedFiles)
{
    static constexpr std::string_view Prefix = "#include \"", Suffix = "\"";

    std::istringstream input{ code };

    usize offset = 0, initialLineLength;
    for (std::string line; std::getline(input, line); offset += initialLineLength)
    {
        initialLineLength = line.length() + 1; // + 1 for '\n'
        line = Utils::Trim(line);

        if (!line.starts_with(Prefix))
            continue;

        std::string filename = line.substr(Prefix.length(), line.find_last_of(Suffix) - Prefix.length());
        std::filesystem::path filepath = (path.parent_path() / filename).lexically_normal();
        if (!FileManager::Contains(filepath))
        {
            Logger::LogError("Shader file {} includes the file {} which is not in the FileManager", path, filepath);
            return;
        }

        code.erase(offset, initialLineLength);

        // If the file has already been processed, ignore it as we already erased it
        if (replacedFiles.contains(filepath))
        {
            initialLineLength = 0;
            continue;
        }

        Pointer file = FileManager::Get(filepath);
        std::string fileContents{file->GetData(), static_cast<usize>(file->GetSize())};
        fileContents = Utils::RemoveByteOrderMark(fileContents);

        ReplaceIncludes(fileContents, filepath, replacedFiles);

        fileContents = std::format("// Include file '{0}' //\n{1}\n// End of include file '{0}' //\n", filename, fileContents);
        code.insert(offset, fileContents);
        replacedFiles.emplace(filepath);

        initialLineLength = fileContents.length();
    }
}
