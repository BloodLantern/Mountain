#include "resource/resource.hpp"

#include "file/file.hpp"
#include "file/file_manager.hpp"
#include "resource/resource_manager.hpp"
// ReSharper disable once CppUnusedIncludeDirective
#include "utils/formatter.hpp"
#include "utils/logger.hpp"

using namespace Mountain;

Resource::Resource(std::string name)
    : m_Name(std::move(name))
    , m_Guid(Guid::New())
{
}

Resource::~Resource() = default;

bool_t Resource::Preload(const uint8_t* const, const int64_t) { return false; }

bool_t Resource::Preload(const Pointer<File>& file)
{
    m_File = file;
    
    return Preload(file->GetData<uint8_t>(), file->GetSize());
}

void Resource::Load() {}

void Resource::Unload() {}

void Resource::PostUnload() {}

bool_t Resource::Reload(const uint8_t* buffer, const int64_t length, const bool_t reloadInBackend)
{
    if (reloadInBackend)
        Unload();
    
    PostUnload();
    
    const bool_t result = Preload(buffer, length);
    
    if (reloadInBackend)
        Load();
    
    return result;
}

bool_t Resource::Reload(const Pointer<File>& file, const bool_t reloadInBackend)
{
    if (reloadInBackend)
        Unload();
    
    PostUnload();
    
    const bool_t result = Preload(file);
    
    if (reloadInBackend)
        Load();
    
    return result;
}

bool_t Resource::Reload(const bool_t reloadInBackend) { return Reload(FileManager::Get(m_Name), reloadInBackend); }

bool_t Resource::IsPreloaded() const { return m_Preloaded; }

bool_t Resource::IsLoaded() const { return m_Loaded; }

std::string Resource::GetName() const { return m_Name; }

void Resource::SetName(std::string newName)
{
    ResourceManager::Rename(m_Name, newName);
    
    m_Name = std::move(newName);
}

void Resource::SetGuid(const Guid& guid) { m_Guid = guid; }

const Guid& Resource::GetGuid() const { return m_Guid; }

void Resource::SetFile(const Pointer<File>& file) { m_File = file; }
