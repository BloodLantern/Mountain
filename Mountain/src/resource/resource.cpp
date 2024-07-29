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

bool_t Resource::Load(const uint8_t* const, const int64_t) { return false; }

bool_t Resource::Load(const Pointer<File>& file)
{
    m_File = file;
    
    return Load(file->GetData<uint8_t>(), file->GetSize());
}

void Resource::CreateInInterface() { m_LoadedInInterface = true; }

void Resource::DestroyInInterface() { m_LoadedInInterface = false; }

void Resource::Unload()
{
}

bool_t Resource::Reload(const uint8_t* buffer, const int64_t length, const bool_t reloadInInterface)
{
    if (reloadInInterface)
        DestroyInInterface();
    
    Unload();
    
    const bool_t result = Load(buffer, length);
    
    if (reloadInInterface)
        CreateInInterface();
    
    return result;
}

bool_t Resource::Reload(const Pointer<File>& file, const bool_t reloadInInterface)
{
    if (reloadInInterface)
        DestroyInInterface();
    
    Unload();
    
    const bool_t result = Load(file);
    
    if (reloadInInterface)
        CreateInInterface();
    
    return result;
}

bool_t Resource::Reload(const bool_t reloadInInterface) { return Reload(FileManager::Get(m_Name), reloadInInterface); }

bool_t Resource::IsLoaded() const { return m_Loaded; }

bool_t Resource::IsLoadedInInterface() const { return m_LoadedInInterface; }

std::string Resource::GetName() const { return m_Name; }

void Resource::SetName(std::string newName)
{
    ResourceManager::Rename(m_Name, newName);
    
    m_Name = std::move(newName);
}

void Resource::SetGuid(const Guid& guid) { m_Guid = guid; }

const Guid& Resource::GetGuid() const { return m_Guid; }

void Resource::SetFile(const Pointer<File>& file) { m_File = file; }
