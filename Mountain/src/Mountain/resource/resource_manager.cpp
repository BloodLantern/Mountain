#include "Mountain/resource/resource_manager.hpp"

#include <array>
#include <execution>

#include "Mountain/file/file_manager.hpp"
#include "Mountain/resource/audio_track.hpp"
#include "Mountain/resource/font.hpp"
#include "Mountain/resource/shader.hpp"
#include "Mountain/resource/texture.hpp"

#include "Mountain/binary_resources/resource_holder.hpp"

namespace rh
{
    namespace
    {
        ResourceHolder embed;
    }
}

using namespace Mountain;

Pointer<Font> ResourceManager::LoadFont(const Pointer<File>& file, const uint32_t size)
{
    Logger::LogDebug("Loading font {} with size {}", file->GetPath(), size);

    std::string name = std::format("{}/{}", ReservedFontPrefix.data() + file->GetPathString(), size);

    Pointer<Font> font;
    
    if (Contains(name))
    {
        font = GetNoCheck<Font>(name);
        Logger::LogWarning("This font has already been loaded, consider using ResourceManager::Get instead");

        font->SetSourceData(file, size);

        return font;
    }
    
    font = Pointer<Font>::New(name);
    
    {
        std::scoped_lock lock(m_ResourcesMutex);
        m_Resources[name] = static_cast<Pointer<Resource>>(font.CreateStrongReference());
    }

    // Make sure to return a weak reference
    font.ToWeakReference();

    font->SetSourceData(file, size);

    return font;
}

Pointer<Font> ResourceManager::LoadFont(const std::string& name, const uint32_t size)
{
    return LoadFont(FileManager::Get(name), size);
}

void ResourceManager::LoadAll()
{
    Logger::LogInfo("Loading all resources from FileManager");

    auto&& start = std::chrono::system_clock::now();

    List<Pointer<File>> files;
    FileManager::FindAll<File>([](Pointer<File> file) { return file->GetResource() == nullptr; }, &files);

    const size_t oldResourceCount = m_Resources.size();

    // Preload resource data asynchronously
    std::for_each(
        std::execution::par,
        files.begin(),
        files.end(),
        [](const Pointer<File>& file) -> void
        {
            std::string&& extension = file->GetExtension();
            
            if (std::ranges::contains(Texture::FileExtensions, extension))
                Load<Texture>(file, false);
            else if (std::ranges::contains(AudioTrack::FileExtensions, extension))
                Load<AudioTrack>(file, false);
        }
    );

    std::vector<Pointer<Shader>> loadedShaders;
    std::vector<Pointer<ComputeShader>> loadedComputeShaders;

    // Do interface stuff synchronously (OpenGL/OpenAL)
    for (Pointer<File>& file : files)
    {
        std::string&& extension = file->GetExtension();

        if (std::ranges::contains(Shader::VertexFileExtensions, extension) || std::ranges::contains(Shader::FragmentFileExtensions, extension))
        {
            Pointer<Shader> shader;

            // We use an underscore before the name to make sure it isn't used elsewhere
            const std::string&& filenameNoExtension = ReservedShaderPrefix.data() + file->GetParent()->GetPathString();
            if (Contains(filenameNoExtension))
                shader = Get<Shader>(filenameNoExtension);
            else
                shader = Add<Shader>(filenameNoExtension);

            shader->SetSourceData(file);
            loadedShaders.push_back(shader);
        }
        else if (std::ranges::contains(ComputeShader::FileExtensions, extension))
        {
            Pointer<ComputeShader> shader;

            // We use an underscore before the name to make sure it isn't used elsewhere
            const std::string&& filenameNoExtension = ReservedComputeShaderPrefix.data() + file->GetParent()->GetPathString();
            if (Contains(filenameNoExtension))
                shader = Get<ComputeShader>(filenameNoExtension);
            else
                shader = Add<ComputeShader>(filenameNoExtension);

            shader->SetSourceData(file);
            loadedComputeShaders.push_back(shader);
        }
        else if (!std::ranges::contains(Font::FileExtensions, extension))
        {
            if (Contains(file))
                Get(file)->Load();
        }
    }

    for (Pointer<Shader>& shader : loadedShaders)
    {
        if (!shader->IsLoaded())
            shader->Load();
    }

    for (Pointer<ComputeShader>& computeShader : loadedComputeShaders)
    {
        if (!computeShader->IsLoaded())
            computeShader->Load();
    }

    Logger::LogDebug(
        "Successfully loaded {} files in {} resources. Took {}",
        files.GetSize(),
        m_Resources.size() - oldResourceCount,
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)
    );
}

void ResourceManager::LoadAllBinaries()
{
    Logger::LogInfo("Loading all embedded binary resources");

    auto&& start = std::chrono::system_clock::now();

    auto&& files = rh::embed.ListFiles();
    const size_t oldResourceCount = m_Resources.size();

    std::vector<Pointer<Shader>> loadedShaders;
    std::vector<Pointer<ComputeShader>> loadedComputeShaders;
    
    for (auto&& file : files)
    {
        std::filesystem::path&& path = file;
        std::string&& extension = path.extension().generic_string();
        
        if (std::ranges::contains(Shader::VertexFileExtensions, extension) || std::ranges::contains(Shader::FragmentFileExtensions, extension))
        {
            Pointer<Shader> shader;

            // We use an underscore before the name to make sure it isn't used elsewhere
            const std::string&& filenameNoExtension = ReservedShaderPrefix.data() + path.parent_path().generic_string();
            if (Contains(filenameNoExtension))
                shader = Get<Shader>(filenameNoExtension);
            else
                shader = Add<Shader>(filenameNoExtension);

            auto&& data = rh::embed(file);
            shader->Load(reinterpret_cast<const char_t*>(data.data()), data.size(), Shader::FileExtensionToType(extension));
            loadedShaders.push_back(shader);
        }
        else if (std::ranges::contains(ComputeShader::FileExtensions, extension))
        {
            Pointer<ComputeShader> shader;

            // We use an underscore before the name to make sure it isn't used elsewhere
            const std::string&& filenameNoExtension = ReservedComputeShaderPrefix.data() + path.parent_path().generic_string();
            if (Contains(filenameNoExtension))
                shader = Get<ComputeShader>(filenameNoExtension);
            else
                shader = Add<ComputeShader>(filenameNoExtension);

            auto&& data = rh::embed(file);
            shader->Load(reinterpret_cast<const char_t*>(data.data()), data.size());
            loadedComputeShaders.push_back(shader);
        }
        else
        {
            Logger::LogWarning("Unhandled binary resource type for file {}", file);
        }
    }

    for (Pointer<Shader>& shader : loadedShaders)
    {
        if (!shader->IsLoaded())
            shader->Load();
    }

    for (Pointer<ComputeShader>& computeShader : loadedComputeShaders)
    {
        if (!computeShader->IsLoaded())
            computeShader->Load();
    }

    Logger::LogDebug(
        "Successfully loaded {} files in {} resources. Took {}",
        files.size(),
        m_Resources.size() - oldResourceCount,
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start)
    );
}

bool ResourceManager::Contains(const std::string& name)
{
    std::scoped_lock lock(m_ResourcesMutex);
    return m_Resources.contains(name);
}

bool ResourceManager::Contains(const Pointer<File>& file)
{
    std::scoped_lock lock(m_ResourcesMutex);
    return m_Resources.contains(file->GetPathString());
}

Pointer<Font> ResourceManager::GetFont(const std::string& name, uint32_t size)
{
    std::string internalName = std::format("{}/{}", ReservedFontPrefix.data() + name, size);
    
    if (!Contains(internalName))
    {
        if (Contains(internalName))
            return GetNoCheck<Font>(internalName);
        
        Logger::LogError("Attempt to get an unknown font: {}", internalName);
        return nullptr;
    }

    return GetNoCheck<Font>(internalName);
}

Pointer<Font> ResourceManager::GetFont(const Pointer<File>& file, uint32_t size)
{
    return GetFont(file->GetPathString(), size);
}

void ResourceManager::Rename(const std::string& name, const std::string& newName)
{
    Rename(Get(name), newName);
}

void ResourceManager::Rename(const Pointer<Resource>& resource, const std::string& newName)
{
    const std::string& oldName = resource->GetName();

    Logger::LogInfo("Renaming resource {} to {}", oldName, newName);

    // Create a new temporary strong reference of the resource to keep it alive until we insert it in the map again
    const Pointer newResource(resource, true);

    m_Resources.erase(oldName);
    // Here we also need to create a new strong reference as the last one will be deleted when going out of scope
    m_Resources[newName] = newResource.CreateStrongReference();
}

void ResourceManager::Unload(const std::string& name)
{
    Logger::LogDebug("Unloading resource {}", name);
    
    const auto&& resource = m_Resources.find(name);
    
    if (resource == m_Resources.end())
    {
        Logger::LogWarning("Attempt to unload an unknown resource: {}", name);
        return;
    }
    
    if (resource->second->IsLoaded())
        resource->second->Unload();

    if (resource->second->IsSourceDataSet())
        resource->second->ResetSourceData();

    m_Resources.erase(resource);
}

void ResourceManager::UnloadAll()
{
    Logger::LogInfo("Unloading all resources ({})", m_Resources.size());

    auto&& start = std::chrono::system_clock::now();
    
    for (auto& resource : m_Resources)
    {
        Logger::LogDebug("Unloading resource {}", resource.first);
        
        if (resource.second->IsLoaded())
            resource.second->Unload();
        
        if (resource.second->IsSourceDataSet())
            resource.second->ResetSourceData();
    }
    // Smart pointers are deleted automatically, we only need to clear the container
    m_Resources.clear();

    Logger::LogInfo("ResourceManager unload successful. Took {}", std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start));
}
