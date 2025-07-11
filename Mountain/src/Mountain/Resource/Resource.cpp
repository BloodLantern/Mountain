﻿#include "Mountain/PrecompiledHeader.hpp"

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

bool_t Resource::SetSourceData(const uint8_t* const, const int64_t) { return false; }

bool_t Resource::SetSourceData(const Pointer<File>& file)
{
    m_File = file;

    return SetSourceData(file->GetData<uint8_t>(), file->GetSize());
}

void Resource::Load() {}

void Resource::Unload() {}

void Resource::ResetSourceData() {}

bool_t Resource::Reload(const uint8_t* buffer, const int64_t length, const bool_t reloadInBackend)
{
    if (reloadInBackend)
        Unload();

    ResetSourceData();

    const bool_t result = SetSourceData(buffer, length);

    if (reloadInBackend)
        Load();

    return result;
}

bool_t Resource::Reload(const Pointer<File>& file, const bool_t reloadInBackend)
{
    if (reloadInBackend)
        Unload();

    ResetSourceData();

    const bool_t result = SetSourceData(file);

    if (reloadInBackend)
        Load();

    return result;
}

bool_t Resource::Reload(const bool_t reloadInBackend) { return Reload(m_File, reloadInBackend); }

bool_t Resource::IsSourceDataSet() const { return m_SourceDataSet; }

bool_t Resource::IsLoaded() const { return m_Loaded; }

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
