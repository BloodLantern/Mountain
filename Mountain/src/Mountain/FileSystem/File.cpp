#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/FileSystem/File.hpp"

#include <fstream>
#include <ranges>

#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Resource/AudioTrack.hpp"
#include "Mountain/Resource/Font.hpp"
#include "Mountain/Resource/Resource.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Resource/Texture.hpp"
#include "Mountain/Utils/Logger.hpp"

using namespace Mountain;

File::File(std::filesystem::path&& filepath)
    : Entry(std::move(filepath))
{
    File::UpdateUtilityValues();
}

File::~File()
{
    if (m_Loaded)
        File::Unload();
}

bool_t File::Load()
{
    std::ifstream file(m_Path, std::ios::in | std::ios::ate | std::ios::binary);

    if (!file.is_open() || !file.good())
    {
        Logger::LogError("Couldn't open file for reading: {}", m_Path);
        return false;
    }

    m_Size = file.tellg();
    file.seekg(0);

    m_Data = new int8_t[m_Size];

    file.read(reinterpret_cast<char*>(m_Data), m_Size);

    m_Loaded = true;
    return true;
}

void File::Load(const char_t* data, const size_t size)
{
    m_Size = static_cast<int64_t>(size);
    m_Data = new int8_t[m_Size];
    std::memcpy(m_Data, data, m_Size);

    m_Loaded = true;
}

void File::Unload()
{
    delete[] m_Data;
    m_Data = nullptr;
    m_Size = 0;

    m_Loaded = false;
}

void File::OpenInExplorer() const
{
    Utils::OpenInExplorer(m_Path, true);
}

void File::OpenFile() const
{
    Utils::OpenFile(m_Path);
}

File::Type File::GetType() const
{
    return m_Type;
}

void File::Delete() const
{
    // We need copies of these variables because they may otherwise be destroyed by FileManager::PostUnload
    const std::filesystem::path path = m_Path;
    const Pointer<Resource> resource = m_Resource;

    FileManager::Unload(path);
    std::filesystem::remove(path);

    if (resource)
        ResourceManager::Unload(resource);
}

bool_t File::Exists()
{
    return exists(m_Path);
}

std::string File::GetNameNoExtension() const
{
    return m_NameNoExtension;
}

std::string File::GetPathNoExtension() const
{
    return m_PathNoExtension;
}

std::string File::GetExtension() const
{
    return m_Extension;
}

int64_t File::GetSize() const
{
    return m_Size;
}

void File::SetName(const std::string& newName)
{
    Entry::SetName(newName);

    m_Resource->SetName(GetPathString());
}

Pointer<Resource> File::GetResource() const
{
    return m_Resource;
}

void File::UpdateUtilityValues()
{
    Entry::UpdateUtilityValues();

    std::filesystem::path path = m_Path;

    m_NameNoExtension = m_Path.stem().generic_string();
    m_Extension = m_Path.extension().generic_string();
    m_PathNoExtension = path.replace_extension().generic_string();

    // Update the file type from the extension
    if (Utils::StringEnumerableContains(AudioTrack::FileExtensions, m_Extension))
        m_Type = Type::AudioTrack;
    else if (Utils::StringEnumerableContains(Texture::FileExtensions, m_Extension))
        m_Type = Type::Texture;
    else if (Utils::StringEnumerableContains(Font::FileExtensions, m_Extension))
        m_Type = Type::Font;
    else if (Utils::StringEqualsIgnoreCase(m_Extension, ".xml"))
        m_Type = Type::Xml;
    else if (Utils::StringEnumerableContains(Shader::VertexFileExtensions, m_Extension))
        m_Type = Type::VertexShader;
    else if (Utils::StringEnumerableContains(Shader::FragmentFileExtensions, m_Extension))
        m_Type = Type::FragmentShader;
    else if (Utils::StringEnumerableContains(ComputeShader::FileExtensions, m_Extension))
        m_Type = Type::ComputeShader;
    else if (Utils::StringEqualsIgnoreCase(m_Extension, ".glsl"))
        m_Type = Type::Glsl;
}
