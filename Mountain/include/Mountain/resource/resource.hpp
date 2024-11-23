#pragma once

#include "Mountain/core.hpp"
#include "Mountain/utils/guid.hpp"
#include "Mountain/utils/pointer.hpp"

BEGIN_MOUNTAIN

/// @file resource.hpp
/// @brief Defines the Mountain::Resource class

class File;

/// @brief Interface for resources, which encapsulates most objects used in the framework that come from a file
///
/// A Resource is loaded in two steps:
/// - @code SetSourceData(const Pointer<File>&)@endcode or @code SetSourceData(const uint8_t*, int64_t)@endcode
/// - @c Load()
/// 
/// And is also unloaded in two steps:
/// - @c Unload()
/// - @c ResetSourceData()
///
/// It can be reloaded using the predefined @c Reload() functions.
class Resource
{
public:
    /// @brief Constructs a default Resource.
    MOUNTAIN_API Resource() = default;

    /// @brief Creates a Resource with the given @p name.
    MOUNTAIN_API explicit Resource(std::string name);

    MOUNTAIN_API virtual ~Resource() = 0;

    DEFAULT_COPY_MOVE_OPERATIONS(Resource)

    /// @brief Loads data from memory.
    ///
    /// @returns @c true if the loading succeeded, @c false otherwise.
    MOUNTAIN_API virtual bool_t SetSourceData(const uint8_t* buffer, int64_t length);

    /// @brief Loads data from file.
    ///
    /// @returns @c true if the loading succeeded, @c false otherwise.
    MOUNTAIN_API virtual bool_t SetSourceData(const Pointer<File>& file);

    /// @brief Loads the Resource in the backend.
    MOUNTAIN_API virtual void Load();

    /// @brief Unloads the Resource in the backend.
    MOUNTAIN_API virtual void Unload();

    /// @brief Resets the source data.
    MOUNTAIN_API virtual void ResetSourceData();

    /// @brief Unloads and then loads back this Resource.
    ///
    /// This is effectively equivalent to calling PostUnload and then @ref Preload(const uint8_t* buffer, int64_t length) "Preload".
    /// 
    /// @returns @c true if the loading succeeded, @c false otherwise.
    MOUNTAIN_API virtual bool_t Reload(const uint8_t* buffer, int64_t length, bool_t reloadInBackend = true);

    /// @brief Unloads and then loads back this Resource.
    ///
    /// This is effectively equivalent to calling PostUnload and then @ref Preload(const Pointer<File>&) "Preload".
    /// 
    /// @returns @c true if the loading succeeded, @c false otherwise.
    MOUNTAIN_API virtual bool_t Reload(const Pointer<File>& file, bool_t reloadInBackend = true);

    /// @brief Unloads and then loads back this Resource.
    ///
    /// This is effectively equivalent to calling PostUnload and then Preload(const Pointer<File>&)
    /// using FileManager::Get(const std::filesystem::path&) as a parameter.
    /// 
    /// @returns @c true if the loading succeeded, @c false otherwise.
    MOUNTAIN_API virtual bool_t Reload(bool_t reloadInBackend = true);

    /// @brief Returns whether the Resource has its source data set.
    [[nodiscard]]
    MOUNTAIN_API bool_t IsSourceDataSet() const;

    /// @brief Returns whether the Resource has already been loaded in the backend.
    [[nodiscard]]
    MOUNTAIN_API bool_t IsLoaded() const;

    /// @brief Returns the name of this Resource.
    [[nodiscard]]
    MOUNTAIN_API const std::string& GetName() const;

    /// @brief Sets the name of this Resource.
    ///
    /// This function also renames the Resource entry in the ResourceManager using ResourceManager::Rename(const std::string&, const std::string&).
    MOUNTAIN_API void SetName(const std::string& newName);

    /// @brief Sets the GUID of this Resource.
    MOUNTAIN_API void SetGuid(const Guid& guid);

    /// @brief Returns the Guid of this Resource.
    [[nodiscard]]
    MOUNTAIN_API const Guid& GetGuid() const;

    /// @brief Returns the File from which this Resource was loaded.
    [[nodiscard]]
    MOUNTAIN_API Pointer<File> GetFile() const;

    MOUNTAIN_API void SetFile(const Pointer<File>& file);

protected:
    /// @brief Whether the Resource has its source data set
    bool_t m_SourceDataSet = false;
    /// @brief Whether the Resource was loaded in the backend
    bool_t m_Loaded = false;

    /// @brief Name of the Resource
    std::string m_Name;
    /// @brief Guid of the Resource
    Guid m_Guid;

    Pointer<File> m_File;

    // We need this in order to set m_File from the ResourceManager
    // which is the only class that needs to modify this field
    friend class ResourceManager;
};

END_MOUNTAIN

#include "Mountain/file/file.hpp"
