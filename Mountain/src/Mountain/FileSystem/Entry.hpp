#pragma once

#include <filesystem>

#include "Mountain/Core.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file entry.hpp
/// @brief Defines the Mountain::Entry class.

namespace Mountain
{
    class Directory;

    /// @brief File system entry. Can be either a File or a Directory.
    class Entry
    {
    public:
        /// @brief Constructs an Entry corresponding to the given @p path.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit Entry(std::filesystem::path&& path);

        /// @brief Default Entry destruction.
        MOUNTAIN_API virtual ~Entry() = default;

        DEFAULT_COPY_MOVE_OPERATIONS(Entry)

        /// @brief Loads the contents of this Entry.
        ///
        /// @returns @c false if an error occured while loading.
        MOUNTAIN_API virtual bool_t Load() = 0;

        /// @brief Unloads the contents of this Entry.
        MOUNTAIN_API virtual void Unload() = 0;

        /// @brief Reloads the contents of this Entry.
        ///
        /// This if effectively the same as calling PostUnload() and then Preload().
        MOUNTAIN_API virtual bool_t Reload();

        /// @brief Opens this Entry in the file explorer
        MOUNTAIN_API virtual void OpenInExplorer() const;

        /// @brief Returns the corresponding filesystem path.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API const std::filesystem::path& GetPath() const;

        /// @brief Returns the string representation of GetPath.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetPathString() const;

        /// @brief Returns this Entry name.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetName() const;

        /// @brief Renames this Entry on the file system.
        ///
        /// This function also renames the File entry in the FileManager using FileManager::Rename(const std::filesystem::path&, const std::filesystem::path&).
        ///
        /// @param newName The new name of this Entry.
        MOUNTAIN_API virtual void SetName(const std::string& newName);

        /// @brief Returns whether this Entry has been loaded.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API bool_t GetLoaded() const;

        /// @brief Sets the new path of this Entry.
        virtual void SetParent(Pointer<Directory>&& newParent);

        /// @brief Returns a Pointer to the parent Directory of this Entry, with a strong reference stored in the FileManager.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Pointer<Directory> GetParent();

    protected:
        /// @brief The underlying filesystem path of this Entry.
        std::filesystem::path m_Path;
        /// @brief The name of this Entry.
        std::string m_Name;

        /// @brief Whether this Entry has been loaded.
        ///
        /// Default implementation of Preload and PostUnload functions in the Entry class already change this value accordingly.
        /// Any override of such function must either call the parent implementation or update this variable so that GetLoaded
        /// returns the correct state.
        bool_t m_Loaded = false;

        /// @brief The parent of this Entry.
        Pointer<Directory> m_Parent;

        /// @brief Updates fields of this class using the new value of m_Path.
        virtual void UpdateUtilityValues();
    };
}

// We cannot include directory.hpp above the class declaration, as the Directory class inherits from Entry.
// However, we also need to include this in every file in which we include entry.hpp, as the Entry class contains a Pointer<Directory>
// which needs the Directory class to be defined at some point so its destructor is defined as well
#include "Mountain/FileSystem/Directory.hpp"
