#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/FileSystem/Entry.hpp"

#include "Mountain/FileSystem/Directory.hpp"
#include "Mountain/FileSystem/FileManager.hpp"

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

void Entry::SetName(const std::string& newName)
{
    std::filesystem::path newPath = m_Path.parent_path() / newName;

    FileManager::Rename(m_Path, newPath);

    m_Path = std::move(newPath);

    UpdateUtilityValues();
}

void Entry::SetParent(Pointer<Directory>&& newParent)
{
    m_Parent = std::move(newParent);
    std::filesystem::path newPath = m_Parent->GetPath() / m_Name;

    if (m_Path == newPath)
        return;

    FileManager::Rename(m_Path, newPath);

    m_Path = std::move(newPath);
}

void Entry::UpdateUtilityValues()
{
    m_PathString = m_Path.generic_string();
    m_Name = m_Path.filename().generic_string();
    const std::filesystem::path parent = m_Path.parent_path();
    if (FileManager::Contains(parent))
        m_Parent = FileManager::Get<Directory>(parent);
}
