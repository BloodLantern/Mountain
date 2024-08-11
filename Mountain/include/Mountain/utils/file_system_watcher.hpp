#pragma once

#include <chrono>
#include <condition_variable>

#include <magic_enum/magic_enum.hpp>

#include "Mountain/core.hpp"
#include "Mountain/utils/event.hpp"

// ReSharper disable once CppInconsistentNaming
// ReSharper disable once CppEnforceTypeAliasCodeStyle
typedef unsigned long DWORD; // Windows type forward declaration  // NOLINT(modernize-use-using)

BEGIN_MOUNTAIN

/// @private
enum class FswNotifyFilters
{
    FileName        = 1 << 0,
    DirectoryName   = 1 << 1,
    Attributes      = 1 << 2,
    Size            = 1 << 3,
    LastWrite       = 1 << 4,
    LastAccess      = 1 << 5,
    Creation        = 1 << 6,
    Security        = 1 << 7,

    Default         = Creation | FileName | DirectoryName | LastWrite,

    All             = FileName | DirectoryName | Attributes | Size | LastWrite | LastAccess | Creation | Security
};

/// @private
class FileSystemWatcher
{
public:
    Event<const std::filesystem::path&> onModified;
    Event<const std::filesystem::path&> onCreated;
    Event<const std::filesystem::path&> onDeleted;
    Event<const std::filesystem::path&, const std::filesystem::path&> onRenamed;

    /// @brief Time between each update.
    std::chrono::milliseconds updateRate{750};

    /// @brief Whether to check the directory contents. Doesn't do anything if the watched path points to a file.
    bool_t checkContents = true;

    /// @brief Whether to check subdirectories. Doesn't do anything if the watched path points to a file or if @c checkContents is @c false
    bool_t recursive = false;

    /// @brief File extensions including the dot '.'
    List<std::string> fileExtensions;

    FswNotifyFilters notifyFilters = FswNotifyFilters::Default;
    
    MOUNTAIN_API FileSystemWatcher() = default;
    
    MOUNTAIN_API explicit FileSystemWatcher(const std::string& path);

    MOUNTAIN_API ~FileSystemWatcher();

    DELETE_COPY_MOVE_OPERATIONS(FileSystemWatcher)

    MOUNTAIN_API void Start();

    MOUNTAIN_API void Stop();

    /// @brief Forces the watcher thread wake up and update now.
    MOUNTAIN_API void Update();

    MOUNTAIN_API std::filesystem::path GetPath() const;

    MOUNTAIN_API void SetPath(const std::filesystem::path& newPath);

    MOUNTAIN_API bool_t GetRunning() const;

private:
    std::thread m_Thread;
    std::condition_variable m_CondVar;
    std::mutex m_Mutex;
    
    std::filesystem::path m_Path;
    bool_t m_IsDirectory = false;

    bool_t m_Running = false;

    bool_t m_PathChanged = false;

    void Run();

    static DWORD NotifyFiltersToWindows(FswNotifyFilters filters);
};

END_MOUNTAIN

ENUM_FLAGS(Mountain::FswNotifyFilters, std::underlying_type_t<Mountain::FswNotifyFilters>)
