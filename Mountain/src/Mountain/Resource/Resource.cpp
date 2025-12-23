

#include "Mountain/Resource/Resource.hpp"

#include "Mountain/FileSystem/File.hpp"
#include "Mountain/FileSystem/FileManager.hpp"
#include "Mountain/Resource/ResourceManager.hpp"
#include "Mountain/Utils/Formatter.hpp"

using namespace Mountain;

Resource::Resource(std::string name)
    : m_Name(std::move(name))
    , m_Guid(Guid::New())
{
}

Resource::~Resource() = default;

bool Resource::SetSourceData(const u8* const, const s64) { return false; }

bool Resource::SetSourceData(const Pointer<File>& file)
{
    m_File = file;

    return SetSourceData(file->GetData<u8>(), file->GetSize());
}

void Resource::Load() {}

void Resource::Unload() {}

void Resource::ResetSourceData() {}

bool Resource::Reload(const u8* buffer, const s64 length, const bool reloadInBackend)
{
    if (reloadInBackend)
        Unload();

    ResetSourceData();

    const bool result = SetSourceData(buffer, length);

    if (reloadInBackend)
        Load();

    return result;
}

bool Resource::Reload(const Pointer<File>& file, const bool reloadInBackend)
{
    if (reloadInBackend)
        Unload();

    ResetSourceData();

    const bool result = SetSourceData(file);

    if (reloadInBackend)
        Load();

    return result;
}

bool Resource::Reload(const bool reloadInBackend) { return Reload(m_File, reloadInBackend); }

bool Resource::IsSourceDataSet() const { return m_SourceDataSet; }

bool Resource::IsLoaded() const { return m_Loaded; }

const std::string& Resource::GetName() const { return m_Name; }

void Resource::SetName(const std::string& newName)
{
    ResourceManager::Rename(m_Name, newName);

    m_Name = newName;
}

void Resource::SetGuid(const Guid& guid) { m_Guid = guid; }

const Guid& Resource::GetGuid() const { return m_Guid; }

Pointer<File> Resource::GetFile() const { return m_File; }

void Resource::SetFile(const Pointer<File>& file) { m_File = file; }
