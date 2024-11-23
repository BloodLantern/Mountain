#pragma once

#include <filesystem>
#include <ranges>

#include "Mountain/utils/formatter.hpp"

BEGIN_MOUNTAIN

template <Concepts::EntryT T>
Pointer<T> FileManager::Get(const std::filesystem::path& path)
{
    if (!Contains(path))
    {
        Logger::LogError("Attempt to get an unknown FileManager entry: {}", path);
        return nullptr;
    }

    return static_cast<Pointer<T>>(m_Entries.at(path));
}

template <Concepts::EntryT T>
Pointer<T> FileManager::Find()
{
    for (auto& entry : m_Entries | std::views::values)
    {
        Pointer<T> t = Utils::DynamicPointerCast<T>(entry);
        
        if (t)
            return t;
    }

    return nullptr;
}

template <Concepts::EntryT T>
Pointer<T> FileManager::Find(std::function<bool_t(Pointer<T>)>&& predicate)
{
    for (auto& entry : m_Entries | std::views::values)
    {
        auto&& t = Utils::DynamicPointerCast<T>(entry);
        
        if (t && predicate(t))
            return t;
    }

    return nullptr;
}

template <Concepts::EntryT T>
std::vector<Pointer<T>> FileManager::FindAll()
{
    std::vector<Pointer<T>> result;
    FindAll<T>(&result);
    return result;
}

template <Concepts::EntryT T>
void FileManager::FindAll(List<Pointer<T>>* result)
{
    result->Clear();
    
    for (auto& entry : m_Entries | std::views::values)
    {
        Pointer<T> t = Utils::DynamicPointerCast<T>(entry);
        
        if (t)
            result->Add(std::move(t));
    }
}

template <Concepts::EntryT T>
List<Pointer<T>> FileManager::FindAll(std::function<bool_t(Pointer<T>)>&& predicate)
{
    List<Pointer<T>> result;
    FindAll<T>(std::forward<std::function<bool_t(Pointer<T>)>>(predicate), &result);
    return result;
}

template <Concepts::EntryT T>
void FileManager::FindAll(std::function<bool_t(Pointer<T>)>&& predicate, List<Pointer<T>>* result)
{
    result->Clear();
    
    for (auto&& value : m_Entries | std::views::values)
    {
        auto&& t = Utils::DynamicPointerCast<T>(value);
        
        if (t && predicate(t))
            result->Add(t);
    }
}

END_MOUNTAIN
