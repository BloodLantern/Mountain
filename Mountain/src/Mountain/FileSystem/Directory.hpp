#pragma once

#include <filesystem>

#include "Mountain/Core.hpp"
#include "Mountain/FileSystem/Entry.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file directory.hpp
/// @brief Defines the Mountain::Directory class.

namespace Mountain
{
    class File;

    /// @brief Defines a directory on the filesystem.
    ///
    /// This is meant to be used with @ref Mountain::Pointer "Pointers" and with the FileManager.
    class Directory : public Entry
    {
    public:
        /// @brief Constructs a Directory corresponding to the given @p path.
        [[nodiscard]]
        MOUNTAIN_API explicit Directory(std::filesystem::path&& filepath);

        /// @brief Default Directory destruction.
        MOUNTAIN_API ~Directory() override = default;

        DEFAULT_COPY_MOVE_OPERATIONS(Directory)

        /// @brief Loads the contents of this Directory in the FileManager.
        ///
        /// This effectively means loading all children of this Directory.
        ///
        /// @returns @c false if an error occured while loading.
        MOUNTAIN_API bool_t Load() override;

        /// @brief Unloads the contents of this Directory.
        MOUNTAIN_API void Unload() override;

        /// @brief Opens this Directory in the file explorer
        MOUNTAIN_API void OpenInExplorer() const override;

        /// @brief Returns all the child @ref Entry "Entries" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API const std::vector<Pointer<Entry>>& GetChildEntries() const;

        /// @brief Returns all the child @ref Entry "Entries" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API std::vector<Pointer<Entry>>& GetChildEntries();

        /// @brief Returns all the child @ref File "Files" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API const std::vector<Pointer<File>>& GetChildFiles() const;

        /// @brief Returns all the child @ref File "Files" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API std::vector<Pointer<File>>& GetChildFiles();

        /// @brief Returns all the child @ref Directory "Directories" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API const std::vector<Pointer<Directory>>& GetChildDirectories() const;

        /// @brief Returns all the child @ref Directory "Directories" of this Directory.
        [[nodiscard]]
        MOUNTAIN_API std::vector<Pointer<Directory>>& GetChildDirectories();

        /// @brief Sets the name of this Directory.
        ///
        /// This effectively means changing the path of all its children accordingly.
        void SetName(const std::string& newName) override;

    private:
        std::vector<Pointer<Entry>> m_ChildEntries;
        std::vector<Pointer<File>> m_ChildFiles;
        std::vector<Pointer<Directory>> m_ChildDirectories;
    };
}

// Voluntary include after the class definition because using Pointer<File> means we need to include File at some point
#include "Mountain/FileSystem/File.hpp"
