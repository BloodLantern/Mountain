#pragma once

#include <filesystem>
#include <map>

#include "Mountain/Core.hpp"
#include "Mountain/FileSystem/Directory.hpp"
#include "Mountain/FileSystem/File.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file FileManager.hpp
/// @brief Defines the Mountain::FileManager class.

namespace Mountain
{
    /// @brief Static class used to add, load, get, or unload @ref File "Files" and @ref Directory "Directories".
    ///
    /// It contains all wrapper instances of the File and Directory classes. These are either added or loaded using the corresponding
    /// function: FileManager::Add and FileManager::Preload for @ref File "Files",and FileManager::AddDirectory and
    /// FileManager::LoadDirectory for @ref Directory "Directories".
    class FileManager final
    {
        STATIC_CLASS(FileManager)

    public:
        /// @brief Creates the File corresponding to the given @p path without loading it.
        MOUNTAIN_API static Pointer<File> Add(std::filesystem::path path);

        /// @brief Creates the File corresponding to the given @p path and loads it.
        MOUNTAIN_API static Pointer<File> Load(std::filesystem::path path);

        /// @brief Creates a Directory corresponding to the given @p path without loading it.
        MOUNTAIN_API static Pointer<Directory> AddDirectory(std::filesystem::path path);

        /// @brief Creates the Directory corresponding to the given @p path and loads it.
        /// @see Directory::Preload
        MOUNTAIN_API static Pointer<Directory> LoadDirectory(std::filesystem::path path);

        /// @brief Checks whether the FileManager contains the specified Entry path.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API static bool_t Contains(const std::filesystem::path& path);

        /// @brief Tries to get the Entry with the given @p path.
        /// @tparam T The type of Entry to get.
        /// @param path The system path to get the Entry of.
        /// @return The Entry corresponding to the given @p path, or nullptr if it hasn't been added yet.
        template <Concepts::Entry T = File>
        ATTRIBUTE_NODISCARD
        static Pointer<T> Get(const std::filesystem::path& path);

        /// @brief Renames the Entry with the specified path to another path.
        ///
        /// @note This function only renames the key used to store this Entry, and doesn't in any case rename the Entry itself.
        /// For this exact reason, using Entry::SetName instead is the preferred way or renaming a Entry.
        MOUNTAIN_API static void Rename(const std::filesystem::path& path, const std::filesystem::path& newPath);

        /// @brief Renames the specified Entry to another path.
        ///
        /// @note This function only renames the key used to store this Entry, and doesn't in any case rename the Entry itself.
        /// For this exact reason, using Entry::SetName instead is the preferred way or renaming a Entry.
        MOUNTAIN_API static void Rename(const Pointer<Entry>& entry, const std::filesystem::path& newPath);

        /// @brief Finds the first Entry of type @p T.
        /// @tparam T The type of Entry to find.
        /// @return The first Entry of type @p T.
        template <Concepts::Entry T = File>
        ATTRIBUTE_NODISCARD
        static Pointer<T> Find();

        /// @brief Finds a specific Entry based on a predicate.
        /// @tparam T The type of Entry to find.
        /// @param predicate The predicate used to find the correct Entry. This function will be
        /// called for each stored Entry.
        /// @return The first Entry for which the @p predicate returned @c true. If every Entry
        /// returned @c false, instead return a null Pointer.
        template <Concepts::Entry T = File>
        ATTRIBUTE_NODISCARD
        static Pointer<T> Find(const std::function<bool_t(const Pointer<T>& element)>& predicate);

        /// @brief Finds all @ref Entry "Entries" of type @p T.
        /// @tparam T The type of Entry to find.
        /// @return All stored @ref Entry "Entries" of type @p T.
        template <Concepts::Entry T = File>
        ATTRIBUTE_NODISCARD
        static List<Pointer<T>> FindAll();

        /// @see FileManager::FindAll()
        template <Concepts::Entry T = File>
        static void FindAll(List<Pointer<T>>* result);

        /// @brief Finds a list of Entry "Entries" based on a predicate.
        /// @tparam T The type of Entry to find.
        /// @param predicate The predicate used to find the correct Entry. This function will be
        /// called for each stored Entry.
        /// @return The first Entry for which the @p predicate returned @c true. If every Entry
        /// returned @c false, instead return a null Pointer.
        template <Concepts::Entry T = File>
        ATTRIBUTE_NODISCARD
        static List<Pointer<T>> FindAll(const std::function<bool_t(const Pointer<T>& element)>& predicate);

        /// @see FileManager::FindAll(std::function<bool(Pointer<T>)>&&)
        template <Concepts::Entry T = File>
        static void FindAll(const std::function<bool_t(const Pointer<T>& element)>& predicate, List<Pointer<T>>* result);

        /// @brief Unloads the Entry corresponding to the given path.
        MOUNTAIN_API static void Unload(const std::filesystem::path& path);

        /// @brief Unloads the given Entry.
        template <Concepts::Entry T>
        static void Unload(const Pointer<T>& entry);

        /// @brief Unloads all stored entries.
        MOUNTAIN_API static void UnloadAll();

    private:
        MOUNTAIN_API static inline std::unordered_map<std::filesystem::path, Pointer<Entry>> m_Entries;
    };
}

// Start of FileManager.inl

#include <ranges>

#include "Mountain/Utils/Formatter.hpp"

namespace Mountain
{
    template <Concepts::Entry T>
    Pointer<T> FileManager::Get(const std::filesystem::path& path)
    {
        if (!Contains(path))
        {
            Logger::LogError("Attempt to get an unknown FileManager entry: {}", path);
            return nullptr;
        }

        return static_cast<Pointer<T>>(m_Entries.at(path));
    }

    template <Concepts::Entry T>
    Pointer<T> FileManager::Find()
    {
        for (const Pointer<Entry>& entry : m_Entries | std::views::values)
        {
            Pointer<T> t = Utils::DynamicPointerCast<T>(entry);

            if (t)
                return t;
        }

        return nullptr;
    }

    template <Concepts::Entry T>
    Pointer<T> FileManager::Find(const Predicate<Pointer<T>>& predicate)
    {
        for (const Pointer<Entry>& entry : m_Entries | std::views::values)
        {
            const Pointer<T>& t = Utils::DynamicPointerCast<T>(entry);

            if (t && predicate(t))
                return t;
        }

        return nullptr;
    }

    template <Concepts::Entry T>
    List<Pointer<T>> FileManager::FindAll()
    {
        List<Pointer<T>> result;
        FindAll<T>(&result);
        return result;
    }

    template <Concepts::Entry T>
    void FileManager::FindAll(List<Pointer<T>>* result)
    {
        result->Clear();

        for (const Pointer<Entry>& entry : m_Entries | std::views::values)
        {
            Pointer<T> t = Utils::DynamicPointerCast<T>(entry);

            if (t)
                result->Add(std::move(t));
        }
    }

    template <Concepts::Entry T>
    List<Pointer<T>> FileManager::FindAll(const Predicate<Pointer<T>>& predicate)
    {
        List<Pointer<T>> result;
        FindAll<T>(std::forward<std::function<bool_t(Pointer<T>)>>(predicate), &result);
        return result;
    }

    template <Concepts::Entry T>
    void FileManager::FindAll(const Predicate<Pointer<T>>& predicate, List<Pointer<T>>* result)
    {
        result->Clear();

        for (const Pointer<Entry>& value : m_Entries | std::views::values)
        {
            const Pointer<T>& t = Utils::DynamicPointerCast<T>(value);

            if (t && predicate(t))
                result->Add(t);
        }
    }

    template <Concepts::Entry T>
    void FileManager::Unload(const Pointer<T>& entry)
    {
        Logger::LogVerbose("Unloading FileManager entry {}", entry);

        const size_t oldSize = m_Entries.size();

        for (auto it = m_Entries.begin(); it != m_Entries.end(); it++)
        {
            if (it->second != entry)
                continue;

            it->second->Unload();
            it = m_Entries.erase(it);

            if (it == m_Entries.end())
                break;
        }

        if (oldSize == m_Entries.size())
            Logger::LogWarning("Attempt to delete an unknown FileManager entry: {}", entry);
    }
}
