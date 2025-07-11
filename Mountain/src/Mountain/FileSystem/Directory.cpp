﻿#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/FileSystem/Directory.hpp"
#include "Mountain/FileSystem/FileManager.hpp"

using namespace Mountain;

Directory::Directory(std::filesystem::path&& filepath)
    : Entry(std::move(filepath))
{
}

bool_t Directory::Load()
{
    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(m_Path))
        {
            const std::filesystem::path& entryPath = entry.path();

            if (is_directory(entryPath))
            {
                Pointer<Directory> directory;
                if (FileManager::Contains(entryPath))
                    directory = FileManager::Get(entryPath);
                else
                    directory = FileManager::LoadDirectory(entryPath);
                m_ChildDirectories.Add(directory);
                m_ChildEntries.Add(static_cast<Pointer<Entry>>(directory));
                continue;
            }

            Pointer<File> file = FileManager::Load(entryPath);
            m_ChildFiles.Add(file);
            m_ChildEntries.Add(static_cast<Pointer<Entry>>(file));
        }
    }
    catch (const std::runtime_error& e)
    {
        Logger::LogError("Uncaught exception while loading directory {}: {}", m_Path, e);
        return false;
    }

    m_Loaded = true;
    return true;
}

void Directory::Unload()
{
    m_ChildEntries.Clear();
    m_ChildFiles.Clear();
    m_ChildDirectories.Clear();
    m_Loaded = false;
}

void Directory::OpenInExplorer() const
{
    Utils::OpenInExplorer(m_Path, false);
}

const List<Pointer<Entry>>& Directory::GetChildEntries() const
{
    return m_ChildEntries;
}

List<Pointer<Entry>>& Directory::GetChildEntries()
{
    return m_ChildEntries;
}

const List<Pointer<File>>& Directory::GetChildFiles() const
{
    return m_ChildFiles;
}

List<Pointer<File>>& Directory::GetChildFiles()
{
    return m_ChildFiles;
}

const List<Pointer<Directory>>& Directory::GetChildDirectories() const
{
    return m_ChildDirectories;
}

List<Pointer<Directory>>& Directory::GetChildDirectories()
{
    return m_ChildDirectories;
}

void Directory::SetName(const std::string& newName)
{
    Entry::SetName(newName);

    for (auto&& entry : GetChildEntries())
        entry->SetParent(FileManager::Get<Directory>(m_Path));
}
