#pragma once

#include <ranges>

#include "Mountain/file/file_manager.hpp"
#include "Mountain/resource/shader.hpp"
#include "Mountain/utils/formatter.hpp"

BEGIN_MOUNTAIN

template <Concepts::LoadableResourceT T>
Pointer<T> ResourceManager::Add(const std::string& name)
{
    Logger::LogDebug("Adding resource {}", name);

    if (Contains(name))
    {
        Logger::LogWarning("The resource {} has already been added, consider using ResourceManager::Get instead", name);
        return GetNoCheck<T>(name);
    }

    Pointer<T> result = AddNoCheck<T>(name);

    Pointer<Resource>(result)->m_File = FileManager::Add(name);
    
    return result;
}

template <>
inline Pointer<Shader> ResourceManager::Add<Shader>(const std::string& name)
{
    const std::string&& n = name.starts_with(ReservedShaderPrefix) ? name : ReservedShaderPrefix.data() + name;
    
    Logger::LogDebug("Adding shader {}", n);

    if (Contains(n))
    {
        Logger::LogWarning("The shader {} has already been added, consider using ResourceManager::Get instead", n);
        return GetNoCheck<Shader>(n);
    }

    return AddNoCheck<Shader>(n);
}

template <Concepts::LoadableResourceT T>
Pointer<T> ResourceManager::Add(const Pointer<File>& file)
{
    return Add<T>(file->GetPathString());
}

template <Concepts::LoadableResourceT T>
Pointer<T> ResourceManager::Load(const Pointer<File>& file, bool_t loadInInterface)
{
    Logger::LogDebug("Loading resource {}", file->GetPath());

    if (Contains(file->GetPathString()))
    {
        Pointer<T> resource = GetNoCheck<T>(file->GetPathString());
        const bool_t loaded = resource->IsSourceDataSet();
        Logger::LogWarning(
            "This resource has already been {}, consider using ResourceManager::Get instead{}",
            loaded ? "loaded" : "added but isn't loaded",
            loaded ? "" : ". Loading it"
        );

        resource->SetSourceData(file);

        return resource;
    }

    return LoadNoCheck<T>(file, loadInInterface);
}

template <Concepts::ResourceT T>
Pointer<T> ResourceManager::Get(const std::string& name)
{
    if (!Contains(name))
    {
        Logger::LogError("Attempt to get an unknown resource: {}", name);
        return nullptr;
    }

    return GetNoCheck<T>(name);
}

template <>
inline Pointer<Shader> ResourceManager::Get<Shader>(const std::string& name)
{
    if (!Contains(name))
    {
        if (Contains(ReservedShaderPrefix.data() + name))
            return GetNoCheck<Shader>(ReservedShaderPrefix.data() + name);
        
        Logger::LogError("Attempt to get an unknown shader: {}", name);
        return nullptr;
    }

    return GetNoCheck<Shader>(name);
}

template <Concepts::ResourceT T>
Pointer<T> ResourceManager::Get(const Pointer<File>& file)
{
    return Get<T>(file->GetPathString());
}

template <Concepts::ResourceT T>
Pointer<T> ResourceManager::Get(const Guid& guid)
{
    auto&& it = m_GuidMap.find(guid);

    if (it == m_GuidMap.end())
        return nullptr;

    return Utils::DynamicPointerCast<T>(GetNoCheck<T>(it->second));
}

template <Concepts::ResourceT T>
List<Pointer<T>> ResourceManager::FindAll()
{
    List<Pointer<T>> result;
    FindAll<T>(&result);
    return result;
}

template <Concepts::ResourceT T>
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

template <Concepts::ResourceT T>
Pointer<T> ResourceManager::Find(std::function<bool_t(Pointer<T>)>&& predicate)
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

template <Concepts::ResourceT T>
List<Pointer<T>> ResourceManager::FindAll(std::function<bool_t(Pointer<T>)>&& predicate)
{
    List<Pointer<T>> result;
    FindAll<T>(FORWARD(predicate), &result);
    return result;
}

template <Concepts::ResourceT T>
void ResourceManager::FindAll(std::function<bool_t(Pointer<T>)>&& predicate, List<Pointer<T>>* result)
{
    result->Clear();

    for (const Pointer<Resource>& val : m_Resources | std::views::values)
    {
        Pointer<T> r = Utils::DynamicPointerCast<T>(val);
        if (r && predicate(r))
            result->Add(r);
    }
}
 
template <Concepts::ResourceT T>
bool_t ResourceManager::IsResourceOfType(const std::string& name)
{
    Pointer<T> resource = Get<T>(name);

    if (resource.IsValid())
        return true;

    return false;
}

template <Concepts::ResourceT T>
void ResourceManager::Unload(const Pointer<T>& resource)
{
    Logger::LogDebug("Unloading resource {}", resource);
    
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

template <Concepts::ResourceT T>
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

template <Concepts::ResourceT T>
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

template <Concepts::ResourceT T>
Pointer<T> ResourceManager::GetNoCheck(const std::string& name)
{
    std::scoped_lock lock(m_ResourcesMutex);
    return Pointer<T>(m_Resources.at(name));
}

END_MOUNTAIN
