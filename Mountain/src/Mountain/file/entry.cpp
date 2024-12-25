#include "Mountain/file/entry.hpp"

#include "Mountain/file/directory.hpp"
#include "Mountain/file/file_manager.hpp"

using namespace Mountain;

Entry::Entry(std::filesystem::path&& path)
    : m_Path(std::move(path))
{
    Entry::UpdateUtilityValues();
}

bool_t Entry::Reload()
{
    if (m_Loaded)
        Unload();
    
    return Load();
}

void Entry::OpenInExplorer() const
{
    Utils::OpenInExplorer(m_Path);
}

const std::filesystem::path& Entry::GetPath() const
{
    return m_Path;
}

std::string Entry::GetPathString() const
{
    return m_Path.generic_string();
}

std::string Entry::GetName() const
{
    return m_Name;
}

void Entry::SetName(const std::string& newName)
{
    std::filesystem::path newPath = m_Path.parent_path().string() + static_cast<char_t>(std::filesystem::path::preferred_separator) + newName;
    std::filesystem::rename(m_Path, newPath);

    FileManager::Rename(m_Path, newPath);

    m_Path = std::move(newPath);

    UpdateUtilityValues();
}

bool_t Entry::GetLoaded() const
{
    return m_Loaded;
}

void Entry::SetParent(Pointer<Directory>&& newParent)
{
    m_Parent = std::move(newParent);
    std::filesystem::path newPath = m_Parent->GetPathString() + static_cast<char_t>(std::filesystem::path::preferred_separator) + m_Name;

    if (m_Path == newPath)
        return;

    FileManager::Rename(m_Path, newPath);

    m_Path = std::move(newPath);
}

Pointer<Directory> Entry::GetParent()
{
    return m_Parent;
}

void Entry::UpdateUtilityValues()
{
    m_Name = m_Path.filename().generic_string();
    const std::filesystem::path parent = m_Path.parent_path();
    if (FileManager::Contains(parent))
        m_Parent = FileManager::Get<Directory>(parent);
}
