module Mountain:FileSystem_Directory;
import :FileSystem_Directory;

import std;
import :Utils;
import :FileSystem_FileManager;

using namespace Mountain;

Directory::Directory(std::filesystem::path&& filepath)
    : Entry(std::move(filepath))
{
}

Directory::~Directory()
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
                m_ChildDirectories.push_back(directory);
                m_ChildEntries.push_back(static_cast<Pointer<Entry>>(directory));
                continue;
            }

            Pointer<File> file = FileManager::Load(entryPath);
            m_ChildFiles.push_back(file);
            m_ChildEntries.push_back(static_cast<Pointer<Entry>>(file));
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
    m_ChildEntries.clear();
    m_ChildFiles.clear();
    m_ChildDirectories.clear();
    m_Loaded = false;
}

void Directory::OpenInExplorer() const
{
    Utils::OpenInExplorer(m_Path, false);
}

const std::vector<Pointer<Entry>>& Directory::GetChildEntries() const
{
    return m_ChildEntries;
}

std::vector<Pointer<Entry>>& Directory::GetChildEntries()
{
    return m_ChildEntries;
}

const std::vector<Pointer<File>>& Directory::GetChildFiles() const
{
    return m_ChildFiles;
}

std::vector<Pointer<File>>& Directory::GetChildFiles()
{
    return m_ChildFiles;
}

const std::vector<Pointer<Directory>>& Directory::GetChildDirectories() const
{
    return m_ChildDirectories;
}

std::vector<Pointer<Directory>>& Directory::GetChildDirectories()
{
    return m_ChildDirectories;
}

void Directory::SetName(const std::string& newName)
{
    Entry::SetName(newName);

    for (auto&& entry : GetChildEntries())
        entry->SetParent(FileManager::Get<Directory>(m_Path));
}
