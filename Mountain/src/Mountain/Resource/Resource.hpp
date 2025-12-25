#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Guid.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file resource.hpp
/// @brief Defines the Mountain::Resource class

namespace Mountain
{
    class File;

    /// @brief Interface for resources, which encapsulates most objects used in the framework that come from a file
    ///
    /// A Resource is loaded in two steps:
    /// - @code SetSourceData(const Pointer<File>&) @endcode or @code SetSourceData(const u8*, s64) @endcode
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
        Resource() = default;

        /// @brief Creates a Resource with the given @p name.
        MOUNTAIN_API explicit Resource(std::string name);

        MOUNTAIN_API virtual ~Resource() = 0;

        DEFAULT_COPY_MOVE_OPERATIONS(Resource)

        /// @brief Loads data from memory.
        ///
        /// @returns @c true if the loading succeeded, @c false otherwise.
        MOUNTAIN_API virtual bool SetSourceData(const u8* buffer, s64 length);

        /// @brief Loads data from a @p file.
        ///
        /// @returns @c true if the loading succeeded, @c false otherwise.
        MOUNTAIN_API virtual bool SetSourceData(const Pointer<File>& file);

        /// @brief Loads the Resource in the backend.
        MOUNTAIN_API virtual void Load();

        /// @brief Unloads the Resource in the backend.
        MOUNTAIN_API virtual void Unload();

        /// @brief Resets the source data.
        MOUNTAIN_API virtual void ResetSourceData();

        /// @brief Unloads and then loads back this Resource.
        ///
        /// This is effectively equivalent to calling ResetSourceData and then @c SetSourceData(const u8* buffer, s64 length).
        ///
        /// @returns @c true if the loading succeeded, @c false otherwise.
        MOUNTAIN_API virtual bool Reload(const u8* buffer, s64 length, bool reloadInBackend = true);

        /// @brief Unloads and then loads back this Resource.
        ///
        /// This is effectively equivalent to calling ResetSourceData and then @c SetSourceData(const Pointer<File>&).
        ///
        /// @returns @c true if the loading succeeded, @c false otherwise.
        MOUNTAIN_API virtual bool Reload(const Pointer<File>& file, bool reloadInBackend = true);

        /// @brief Unloads and then loads back this Resource.
        ///
        /// This is effectively equivalent to calling @c ResetSourceData()
        /// and then @code SetSourceData(const Pointer<File>&)@endcode
        /// using @code FileManager::Get(const std::filesystem::path&)@endcode as a parameter.
        ///
        /// @returns @c true if the loading succeeded, @c false otherwise.
        MOUNTAIN_API virtual bool Reload(bool reloadInBackend = true);

        /// @brief Returns whether the Resource has its source data set.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool IsSourceDataSet() const;

        /// @brief Returns whether the Resource has already been loaded in the backend.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool IsLoaded() const;

        /// @brief Returns the name of this Resource.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const std::string& GetName() const;

        /// @brief Sets the name of this Resource.
        ///
        /// This function also renames the Resource entry in the ResourceManager using ResourceManager::Rename(const std::string&, const std::string&).
        MOUNTAIN_API void SetName(const std::string& newName);

        /// @brief Sets the GUID of this Resource.
        MOUNTAIN_API void SetGuid(const Guid& guid);

        /// @brief Returns the Guid of this Resource.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const Guid& GetGuid() const;

        /// @brief Returns the File from which this Resource was loaded.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Pointer<File> GetFile() const;

        MOUNTAIN_API void SetFile(const Pointer<File>& file);

    protected:
        /// @brief Whether the Resource has its source data set
        bool m_SourceDataSet = false;
        /// @brief Whether the Resource was loaded in the backend
        bool m_Loaded = false;

        /// @brief Name of the Resource
        std::string m_Name;
        /// @brief Guid of the Resource
        Guid m_Guid;

        Pointer<File> m_File;

        // We need this to set m_File from the ResourceManager
        // which is the only class that needs to modify this field
        friend class ResourceManager;
    };
}

#include "Mountain/FileSystem/File.hpp"
