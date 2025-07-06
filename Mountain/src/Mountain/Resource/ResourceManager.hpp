#pragma once

#include <unordered_map>

#include "Mountain/FileSystem/File.hpp"
#include "Mountain/Resource/Resource.hpp"
#include "Mountain/Containers/List.hpp"
#include "Mountain/Utils/Logger.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file ResourceManager.hpp
/// @brief Defines the Mountain::ResourceManager class.

namespace Mountain
{
    /// @brief Static class used to add, load, get, or unload @ref Mountain::Resource "Resources".
    ///
    /// It contains all wrapper instances of the Resource class. These are either added or loaded using the corresponding
    /// function: ResourceManager::Add and ResourceManager::Preload.
    class ResourceManager final
    {
        STATIC_CLASS(ResourceManager)

    public:
        /// @brief Creates the Resource corresponding to the given @p name without loading it.
        template <Concepts::LoadableResource T>
        static Pointer<T> Add(const std::string& name);

        /// @brief Creates the Resource corresponding to the given @p file without loading it.
        template <Concepts::LoadableResource T>
        static Pointer<T> Add(const Pointer<File>& file);

        /// @brief Creates the Resource corresponding to the given @p file and loads it.
        template <Concepts::LoadableResource T>
        static Pointer<T> Load(const Pointer<File>& file, bool_t loadInInterface = true);

        /// @brief Creates the Font corresponding to the given @p file and loads it with the given @p size.
        MOUNTAIN_API static Pointer<Font> LoadFont(const Pointer<File>& file, uint32_t size);

        /// @brief Creates the Font corresponding to the given @p name and loads it with the given @p size.
        MOUNTAIN_API static Pointer<Font> LoadFont(const std::string& name, uint32_t size);

        /// @brief Creates one Resource for each @ref FileManager entry.
        MOUNTAIN_API static void LoadAll();

        /// @brief Loads all embedded binary Resources created using @c std::embed.
        /// @see <a href="https://github.com/MKlimenko/embed">std::embed</a>
        MOUNTAIN_API static void LoadAllBinaries();

        /// @brief Checks whether the ResourceManager contains the specified Resource name.
        [[nodiscard]]
        MOUNTAIN_API static bool_t Contains(const std::string& name);

        /// @brief Checks whether the ResourceManager contains the specified Resource file name.
        [[nodiscard]]
        MOUNTAIN_API static bool_t Contains(const Pointer<File>& file);

        /// @brief Checks whether the given Resource name is an embedded binary Resource.
        /// @see LoadAllBinaries()
        [[nodiscard]]
        MOUNTAIN_API static bool_t IsBinary(const std::string& name);

        /// @brief Returns the Resource that was either added or loaded using the given @p name.
        template <Concepts::Resource T = Resource>
        [[nodiscard]]
        static Pointer<T> Get(const std::string& name);

        /// @brief Returns the Resource that was either added or loaded using the given file name.
        template <Concepts::Resource T = Resource>
        [[nodiscard]]
        static Pointer<T> Get(const Pointer<File>& file);

        /// @brief Returns the Font that was loaded using the given @p name and @p size.
        [[nodiscard]]
        MOUNTAIN_API static Pointer<Font> GetFont(const std::string& name, uint32_t size);

        /// @brief Returns the Font that was loaded using the given @p file and @p size.
        [[nodiscard]]
        MOUNTAIN_API static Pointer<Font> GetFont(const Pointer<File>& file, uint32_t size);

        /// @brief Returns the Resource that was either added or loaded using the given file name.
        template <Concepts::Resource T = Resource>
        [[nodiscard]]
        static Pointer<T> Get(const Guid& guid);

        /// @brief Renames the Resource with the given @p name to @p newName.
        ///
        /// @note This function only renames the key used to store this Resource, and doesn't in any case rename the Resource itself.
        /// For this exact reason, using Resource::SetName instead is the preferred way or renaming a Resource.
        MOUNTAIN_API static void Rename(const std::string& name, const std::string& newName);

        /// @brief Renames the given @p resource to @p newName.
        ///
        /// @note This function only renames the key used to store this Resource, and doesn't in any case rename the Resource itself.
        /// For this exact reason, using Resource::SetName instead is the preferred way or renaming a Resource.
        MOUNTAIN_API static void Rename(const Pointer<Resource>& resource, const std::string& newName);

        /// @brief Finds all Resource of type @p T.
        /// @tparam T The type of Resource to find.
        /// @return All stored Resource of type @p T.
        template <Concepts::Resource T>
        [[nodiscard]]
        static List<Pointer<T>> FindAll();

        /// @see ResourceManager::FindAll()
        template <Concepts::Resource T>
        static void FindAll(List<Pointer<T>>* result);

        /// @brief Finds a specific Resource based on a predicate.
        /// @tparam T The type of Resource to find.
        /// @param predicate The predicate used to find the correct Resource. This function will be
        /// called for each stored Resource.
        /// @return The first Resource for which the @p predicate returned @c true. If every Resource
        /// returned @c false, instead return a null @ref Pointer.
        template <Concepts::Resource T = Resource>
        [[nodiscard]]
        static Pointer<T> Find(const std::function<bool_t(Pointer<T>)>& predicate);

        /// @brief Finds a list of Resource based on a predicate.
        /// @tparam T The type of Resource to find.
        /// @param predicate The predicate used to find the correct Resource. This function will be
        /// called for each stored Resource.
        /// @return The first Resource for which the @p predicate returned @c true. If every Resource
        /// returned @c false, instead return a null @ref Pointer.
        template <Concepts::Resource T = Resource>
        [[nodiscard]]
        static List<Pointer<T>> FindAll(const std::function<bool_t(Pointer<T>)>& predicate);

        /// @see @ref FileManager::FindAll(std::function<bool_t(Pointer<T>)>&&)
        template <Concepts::Resource T>
        static void FindAll(const std::function<bool_t(Pointer<T>)>& predicate, List<Pointer<T>>* result);

        /// @brief Checks whether the given @p name corresponds to a Resource of type @p T.
        template <Concepts::Resource T>
        [[nodiscard]]
        static bool_t IsResourceOfType(const std::string& name);

        /// @brief Unloads the Resource with the given @p name.
        MOUNTAIN_API static void Unload(const std::string& name);

        /// @brief Unloads the given @p resource.
        template <Concepts::Resource T>
        static void Unload(const Pointer<T>& resource);

        /// @brief Unloads all stored @ref Mountain::Resource "Resources".
        MOUNTAIN_API static void UnloadAll();

    private:
        MOUNTAIN_API static inline std::unordered_map<std::string, Pointer<Resource>> m_Resources;
        MOUNTAIN_API static inline std::mutex m_ResourcesMutex;
        MOUNTAIN_API static inline std::unordered_map<Guid, std::string> m_GuidMap;

        template <Concepts::Resource T>
        static Pointer<T> AddNoCheck(std::string name);

        template <Concepts::Resource T>
        static Pointer<T> LoadNoCheck(Pointer<File> file, bool_t loadInRhi = true);

        template <Concepts::Resource T>
        [[nodiscard]]
        static Pointer<T> GetNoCheck(const std::string& name);
    };
}

// Start of ResourceManager.inl

#include <ranges>

#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Resource/ComputeShader.hpp"
#include "Mountain/Resource/Shader.hpp"
#include "Mountain/Utils/Formatter.hpp"

namespace Mountain
{
    template <Concepts::LoadableResource T>
    Pointer<T> ResourceManager::Add(const std::string& name)
    {
        Logger::LogVerbose("Adding resource {}", name);

        if (Contains(name))
        {
            Logger::LogWarning("The resource {} has already been added, consider using ResourceManager::Get instead", name);
            return GetNoCheck<T>(name);
        }

        Pointer<T> result = AddNoCheck<T>(name);

        return result;
    }

    template <Concepts::LoadableResource T>
    Pointer<T> ResourceManager::Add(const Pointer<File>& file)
    {
        return Add<T>(file->GetPathString());
    }

    template <Concepts::LoadableResource T>
    Pointer<T> ResourceManager::Load(const Pointer<File>& file, const bool_t loadInInterface)
    {
        Logger::LogVerbose("Loading resource {}", file->GetPath());

        if (Contains(file->GetPathString()))
        {
            Pointer<T> resource = GetNoCheck<T>(file->GetPathString());
            const bool_t loaded = resource->IsSourceDataSet();
            Logger::LogWarning(
                "This resource has already been {}, consider using ResourceManager::Get instead{}",
                loaded ? "loaded" : "added but isn't loaded",
                loaded ? "" : ". Loading it"
            );

            if (loaded)
                resource->SetSourceData(file);

            return resource;
        }

        return LoadNoCheck<T>(file, loadInInterface);
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::Get(const std::string& name)
    {
        if (!Contains(name))
        {
            Logger::LogError("Attempt to get an unknown resource: {}", name);
            return nullptr;
        }

        return GetNoCheck<T>(name);
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::Get(const Pointer<File>& file)
    {
        return Get<T>(file->GetPathString());
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::Get(const Guid& guid)
    {
        auto&& it = m_GuidMap.find(guid);

        if (it == m_GuidMap.end())
            return nullptr;

        return Utils::DynamicPointerCast<T>(GetNoCheck<T>(it->second));
    }

    template <Concepts::Resource T>
    List<Pointer<T>> ResourceManager::FindAll()
    {
        List<Pointer<T>> result;
        FindAll<T>(&result);
        return result;
    }

    template <Concepts::Resource T>
    void ResourceManager::FindAll(List<Pointer<T>>* result)
    {
        result->Clear();

        for (auto& val : m_Resources | std::views::values)
        {
            Pointer<T> entry = Utils::DynamicPointerCast<T>(val);

            if (entry)
                result->Add(std::move(entry));
        }
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::Find(const std::function<bool_t(Pointer<T>)>& predicate)
    {
        for (const auto& val : m_Resources | std::views::values)
        {
            Pointer<Resource> resource = val;

            Pointer<T> r = Utils::DynamicPointerCast<T>(val);
            if (r && predicate(r))
                return r;
        }

        return nullptr;
    }

    template <Concepts::Resource T>
    List<Pointer<T>> ResourceManager::FindAll(const std::function<bool_t(Pointer<T>)>& predicate)
    {
        List<Pointer<T>> result;
        FindAll<T>(predicate, &result);
        return result;
    }

    template <Concepts::Resource T>
    void ResourceManager::FindAll(const std::function<bool_t(Pointer<T>)>& predicate, List<Pointer<T>>* result)
    {
        result->Clear();

        for (const Pointer<Resource>& val : m_Resources | std::views::values)
        {
            Pointer<T> r = Utils::DynamicPointerCast<T>(val);
            if (r && predicate(r))
                result->Add(r);
        }
    }

    template <Concepts::Resource T>
    bool_t ResourceManager::IsResourceOfType(const std::string& name)
    {
        Pointer<T> resource = Get<T>(name);

        if (resource.IsValid())
            return true;

        return false;
    }

    template <Concepts::Resource T>
    void ResourceManager::Unload(const Pointer<T>& resource)
    {
        Logger::LogVerbose("Unloading resource {}", resource);

        const size_t oldSize = m_Resources.size();

        for (decltype(m_Resources)::iterator it = m_Resources.begin(); it != m_Resources.end(); it++)
        {
            Pointer<Resource>& storedResource = it->second;
            if (storedResource == Utils::DynamicPointerCast<Resource>(resource))
            {
                if (storedResource->IsLoaded())
                    storedResource->Unload();

                if (storedResource->IsSourceDataSet())
                    storedResource->ResetSourceData();

                it = m_Resources.erase(it);

                if (it == m_Resources.end())
                    break;
            }
        }

        // If no resources were deleted
        if (oldSize == m_Resources.size())
            Logger::LogWarning("Attempt to unload an unknown file entry: {}", resource);
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::AddNoCheck(std::string name)
    {
        Pointer<T> resource = Pointer<T>::New(std::forward<std::string>(name));

        {
            std::scoped_lock lock(m_ResourcesMutex);
            // We cannot reuse the variable 'name' here in case it was moved inside the Resource constructor
            m_Resources[resource->GetName()] = static_cast<Pointer<Resource>>(resource.CreateStrongReference());
        }

        // Make sure to return a weak reference
        resource.ToWeakReference();

        return resource;
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::LoadNoCheck(Pointer<File> file, const bool_t loadInRhi)
    {
        Pointer<T> resource = Pointer<T>::New(file->GetPathString());

        {
            std::scoped_lock lock(m_ResourcesMutex);
            m_Resources[resource->GetName()] = static_cast<Pointer<Resource>>(resource.CreateStrongReference());
        }

        // Make sure to return a weak reference
        resource.ToWeakReference();

        resource->SetSourceData(file);

        file->m_Resource = Pointer<Resource>(resource, false);

        if (loadInRhi)
            resource->Load();

        return resource;
    }

    template <Concepts::Resource T>
    Pointer<T> ResourceManager::GetNoCheck(const std::string& name)
    {
        std::scoped_lock lock(m_ResourcesMutex);
        return Pointer<T>(m_Resources.at(name));
    }
}
