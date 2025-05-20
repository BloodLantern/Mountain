#include "Mountain/FileSystem/FileManager.ixx"

using namespace Mountain;

Pointer<File> FileManager::Add(std::filesystem::path path)
{
    Logger::LogVerbose("Adding file {}", path);

    if (Contains(path))
    {
        Logger::LogWarning("The file {} has already been added, consider using FileManager::Get instead", path);
        return static_cast<Pointer<File>>(m_Entries.at(path));
    }

    Pointer<File> file;
    try
    {
        file = Pointer<File>::New(std::forward<std::filesystem::path>(path));
    }
    catch (const std::invalid_argument& ex)
    {
        Logger::LogError("Exception while creating file with path {}: {}", path, ex.what());
        // Return the already-constructed null Pointer
        return file;
    }

    m_Entries[file->GetPath()] = file.CreateStrongReference();

    // Make sure to return a weak reference
    file.ToWeakReference();

    return file;
}

Pointer<File> FileManager::Load(std::filesystem::path path)
{
    Logger::LogVerbose("Loading file {}", path);

    if (Contains(path))
    {
        Pointer<File> file = static_cast<Pointer<File>>(m_Entries.at(path));
        const bool loaded = file->GetLoaded();
        Logger::LogWarning(
            "This file has already been {}, consider using FileManager::Get instead{}",
            loaded ? "loaded" : "added but isn't loaded",
            loaded ? "" : ". Loading it"
        );
        if (!loaded)
            file->Load();
        return file;
    }

    Pointer<File> file;
    try
    {
        file = Pointer<File>::New(std::forward<std::filesystem::path>(path));
    }
    catch (const std::invalid_argument& ex)
    {
        Logger::LogError("Exception while creating file with path {}: {}", path, ex.what());
        // Return the already-constructed null Pointer
        return file;
    }

    if (!file->Load())
        throw std::runtime_error("An error occured while loading file");

    m_Entries[file->GetPath()] = file.CreateStrongReference();

    // Make sure to return a weak reference
    file.ToWeakReference();

    return file;
}

Pointer<Directory> FileManager::AddDirectory(std::filesystem::path path)
{
    Logger::LogVerbose("Adding directory {}", path);

    if (Contains(path))
    {
        Logger::LogWarning("The directory {} has already been added, consider using FileManager::Get instead", path);
        return static_cast<Pointer<Directory>>(m_Entries.at(path));
    }

    Pointer<Directory> directory;
    try
    {
        directory = Pointer<Directory>::New(std::forward<std::filesystem::path>(path));
    }
    catch (const std::invalid_argument& ex)
    {
        Logger::LogError("Exception while creating directory with path {}: {}", path, ex.what());
        // Return the already-constructed null Pointer
        return directory;
    }

    m_Entries[directory->GetPath()] = directory.CreateStrongReference();

    // Make sure to return a weak reference
    directory.ToWeakReference();

    return directory;
}

Pointer<Directory> FileManager::LoadDirectory(std::filesystem::path path)
{
    Logger::LogInfo("Loading directory {}...", path);

    auto&& start = std::chrono::system_clock::now();

    if (Contains(path))
    {
        Pointer<Directory> directory = static_cast<Pointer<Directory>>(m_Entries.at(path));
        const bool loaded = directory->GetLoaded();
        Logger::LogWarning(
            "The directory {} has already been {}, consider using FileManager::Get instead{}", path,
            loaded ? "loaded" : "added but isn't loaded",
            loaded ? "" : ". Loading it"
        );
        if (!loaded)
            directory->Load();
        return directory;
    }

    Pointer<Directory> directory;
    try
    {
        directory = Pointer<Directory>::New(std::move(path));
    }
    catch (const std::invalid_argument& ex)
    {
        Logger::LogError("Exception while creating directory with path {}: {}", directory->GetPath(), ex.what());
        // Return the already-constructed null Pointer
        return directory;
    }

    const std::filesystem::path& p = directory->GetPath();

    m_Entries[p] = directory.CreateStrongReference();

    if (!directory->Load())
    {
        m_Entries.erase(p);
        throw std::runtime_error("An error occured while loading directory");
    }

    // Make sure to return a weak reference
    directory.ToWeakReference();

    Logger::LogVerbose("Directory {} load successful. Took {}", p, std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start));

    return directory;
}

bool_t FileManager::Contains(const std::filesystem::path& path)
{
    return m_Entries.contains(path);
}

void FileManager::Rename(const std::filesystem::path& path, const std::filesystem::path& newPath)
{
    Rename(Get<Entry>(path), newPath);
}

void FileManager::Rename(const Pointer<Entry>& entry, const std::filesystem::path& newPath)
{
    std::string&& oldName = entry->GetPathString();

    Logger::LogInfo("Renaming FileManager entry {} to {}", oldName, newPath);

    // Create a new temporary strong reference of the entry to keep it alive until we insert it in the map again
    const Pointer newEntry(entry, true);

    m_Entries.erase(oldName);
    // Here we also need to create a new strong reference as the last one will be deleted when going out of scope
    m_Entries[newPath] = newEntry.CreateStrongReference();
}

void FileManager::Unload(const std::filesystem::path& path)
{
    Logger::LogVerbose("Unloading FileManager entry {}", path);

    if (!exists(path))
    {
        Logger::LogError("Path does not exist");
        return;
    }

    const size_t oldSize = m_Entries.size();

    for (decltype(m_Entries)::iterator it = m_Entries.begin(); it != m_Entries.end(); it++)
    {
        if (equivalent(it->first, path))
        {
            it->second->Unload();
            it = m_Entries.erase(it);

            if (it == m_Entries.end())
                break;
        }
    }

    if (oldSize == m_Entries.size())
        Logger::LogWarning("Attempt to delete an unknown FileManager entry: {}", path);
}

void FileManager::Unload(const Pointer<Entry>& entry)
{
    Logger::LogVerbose("Unloading FileManager entry {}", entry);

    const size_t oldSize = m_Entries.size();

    for (decltype(m_Entries)::iterator it = m_Entries.begin(); it != m_Entries.end(); it++)
    {
        if (it->second == entry)
        {
            it->second->Unload();
            it = m_Entries.erase(it);

            if (it == m_Entries.end())
                break;
        }
    }

    if (oldSize == m_Entries.size())
        Logger::LogWarning("Attempt to delete an unknown FileManager entry: {}", entry);
}

void FileManager::UnloadAll()
{
    Logger::LogInfo("Unloading all FileManager entries ({})", m_Entries.size());

    auto&& start = std::chrono::system_clock::now();

    for (auto&& entry : m_Entries)
    {
        Logger::LogVerbose("Unloading FileManager entry {}", entry.first);

        if (entry.second->GetLoaded())
            entry.second->Unload();
    }

    // Smart pointers are deleted automatically, we only need to clear the container
    m_Entries.clear();

    Logger::LogVerbose("FileManager unload successful. Took {}", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start));
}
