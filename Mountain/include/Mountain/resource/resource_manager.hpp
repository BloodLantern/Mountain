#pragma once

#include <unordered_map>

#include "Mountain/file/file.hpp"
#include "Mountain/resource/resource.hpp"
#include "Mountain/utils/list.hpp"
#include "Mountain/utils/logger.hpp"
#include "Mountain/utils/pointer.hpp"

/// @file resource_manager.hpp
/// @brief Defines the Mountain::ResourceManager class.

BEGIN_MOUNTAIN

/// @brief Static class used to add, load, get, or unload @ref Mountain::Resource "Resources".
///
/// It contains all wrapper instances of the Resource class. These are either added or loaded using the corresponding
/// function: ResourceManager::Add and ResourceManager::Preload.
class ResourceManager final
{
    STATIC_CLASS(ResourceManager)
    
public:
    /// @brief Special prefix used to store added @ref Shader "Shaders"
    ///
    /// This is mainly used in @c LoadAll() and @c LoadAllBinaries()
    static constexpr std::string_view ReservedShaderPrefix = "_shaders/";

    /// @brief Special prefix used to store added @ref ComputeShader "Compute Shaders"
    ///
    /// This is mainly used in @c LoadAll() and @c LoadAllBinaries()
    static constexpr std::string_view ReservedComputeShaderPrefix = "_compute_shaders/";
    
    /// @brief Special prefix used to store added @ref Font "Fonts"
    ///
    /// This is used to differentiate fonts that use the same file but different sizes
    static constexpr std::string_view ReservedFontPrefix = "_fonts/";
    
    /// @brief Creates the Resource corresponding to the given @p name without loading it.
    template <Concepts::LoadableResourceT T>
    static Pointer<T> Add(const std::string& name);
    
    /// @brief Creates the Resource corresponding to the given @p file without loading it.
    template <Concepts::LoadableResourceT T>
    static Pointer<T> Add(const Pointer<File>& file);

    /// @brief Creates the Resource corresponding to the given @p file and loads it.
    template <Concepts::LoadableResourceT T>
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

    /// @brief Returns the Resource that was either added or loaded using the given @p name.
    template <Concepts::ResourceT T = Resource>
    [[nodiscard]]
    static Pointer<T> Get(const std::string& name);

    /// @brief Returns the Resource that was either added or loaded using the given file name.
    template <Concepts::ResourceT T = Resource>
    [[nodiscard]]
    static Pointer<T> Get(const Pointer<File>& file);

    /// @brief Returns the Font that was loaded using the given @p name and @p size.
    [[nodiscard]]
    MOUNTAIN_API static Pointer<Font> GetFont(const std::string& name, uint32_t size);

    /// @brief Returns the Font that was loaded using the given @p file and @p size.
    [[nodiscard]]
    MOUNTAIN_API static Pointer<Font> GetFont(const Pointer<File>& file, uint32_t size);

    /// @brief Returns the Resource that was either added or loaded using the given file name.
    template <Concepts::ResourceT T = Resource>
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
    template <Concepts::ResourceT T>
    [[nodiscard]]
    static List<Pointer<T>> FindAll();
    
    /// @see ResourceManager::FindAll()
    template <Concepts::ResourceT T>
    static void FindAll(List<Pointer<T>>* result);

    /// @brief Finds a specific Resource based on a predicate.
    /// @tparam T The type of Resource to find.
    /// @param predicate The predicate used to find the correct Resource. This function will be
    /// called for each stored Resource.
    /// @return The first Resource for which the @p predicate returned @c true. If every Resource
    /// returned @c false, instead return a null @ref Pointer.
    template <Concepts::ResourceT T = Resource>
    [[nodiscard]]
    static Pointer<T> Find(std::function<bool_t(Pointer<T>)>&& predicate);
    
    /// @brief Finds a list of Resource based on a predicate.
    /// @tparam T The type of Resource to find.
    /// @param predicate The predicate used to find the correct Resource. This function will be
    /// called for each stored Resource.
    /// @return The first Resource for which the @p predicate returned @c true. If every Resource
    /// returned @c false, instead return a null @ref Pointer.
    template <Concepts::ResourceT T = Resource>
    [[nodiscard]]
    static List<Pointer<T>> FindAll(std::function<bool_t(Pointer<T>)>&& predicate);

    /// @see @ref FileManager::FindAll(std::function<bool_t(Pointer<T>)>&&)
    template <Concepts::ResourceT T>
    static void FindAll(std::function<bool_t(Pointer<T>)>&& predicate, List<Pointer<T>>* result);

    /// @brief Checks whether the given @p name corresponds to a Resource of type @p T.
    template <Concepts::ResourceT T>
    [[nodiscard]]
    static bool_t IsResourceOfType(const std::string& name);

    /// @brief Unloads the Resource with the given @p name.
    MOUNTAIN_API static void Unload(const std::string& name);

    /// @brief Unloads the given @p resource.
    template <Concepts::ResourceT T>
    static void Unload(const Pointer<T>& resource);

    /// @brief Unloads all stored @ref Mountain::Resource "Resources".
    MOUNTAIN_API static void UnloadAll();

private:
    MOUNTAIN_API static inline std::unordered_map<std::string, Pointer<Resource>> m_Resources;
    MOUNTAIN_API static inline std::mutex m_ResourcesMutex;
    MOUNTAIN_API static inline std::unordered_map<Guid, std::string> m_GuidMap;
    
    template <Concepts::ResourceT T>
    static Pointer<T> AddNoCheck(std::string name);
    
    template <Concepts::ResourceT T>
    static Pointer<T> LoadNoCheck(Pointer<File> file, bool_t loadInRhi = true);

    template <Concepts::ResourceT T>
    [[nodiscard]]
    static Pointer<T> GetNoCheck(const std::string& name);
};

END_MOUNTAIN

#include "Mountain/resource/resource_manager.inl"
