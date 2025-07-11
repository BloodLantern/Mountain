#pragma once

#include <filesystem>

#include "Mountain/Core.hpp"
#include "Mountain/FileSystem/Entry.hpp"
#include "Mountain/Resource/Resource.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file File.hpp
/// @brief Defines the Mountain::File class.

namespace Mountain
{
    /// @brief Defines a file on the filesystem.
    ///
    /// This is meant to be used with @ref Mountain::Pointer "Pointers" and with the FileManager.
    class File : public Entry
    {
    public:
        /// @brief Type of file according to file extension.
        enum class Type : uint8_t
        {
            Unknown,
            AudioTrack,
            Texture,
            Font,
            Xml,
            VertexShader,
            FragmentShader,
            ComputeShader,
            Glsl
        };

        /// @brief Constructs a File corresponding to the given @p path.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API explicit File(std::filesystem::path&& filepath);

        /// @brief Destructs the File instance by calling PostUnload.
        MOUNTAIN_API ~File() override;

        DEFAULT_COPY_MOVE_OPERATIONS(File)

        /// @brief Loads the contents of this File.
        ///
        /// @returns @c false if an error occured while loading.
        MOUNTAIN_API bool_t Load() override;

        /// @brief Loads the given contents in this File.
        /// Note: This doesn't have anything to do with the file system. This only loads the given data in this resource.
        MOUNTAIN_API void Load(const char_t* data, size_t size);

        /// @brief Unloads the contents of this File.
        MOUNTAIN_API void Unload() override;

        /// @brief Opens this File in the file explorer
        MOUNTAIN_API void OpenInExplorer() const override;

        /// @brief Opens this File on the user's computer using the default software for its file extension
        MOUNTAIN_API void OpenFile() const;

        /// @brief Returns the Type of this File.
        MOUNTAIN_API Type GetType() const;

        /// @brief Deletes the corresponding filesystem file.
        MOUNTAIN_API void Delete() const;

        /// @brief Get whether this file exists on the file system or is just a virtual file representation
        MOUNTAIN_API bool_t Exists();

        /// @brief Returns the name of this File without the file extension.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetNameNoExtension() const;

        /// @brief Returns the name of this File without the file extension.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetPathNoExtension() const;

        /// @brief Returns the file extension of this File.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API std::string GetExtension() const;

        /// @brief Returns a @c const pointer to the raw loaded data.
        template <typename T = char_t>
        ATTRIBUTE_NODISCARD
        const T* GetData() const;

        /// @brief Returns a pointer to the raw loaded data.
        template <typename T = char_t>
        ATTRIBUTE_NODISCARD
        T* GetData();

        /// @brief Returns the size of the loaded data.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API int64_t GetSize() const;

        /// @brief Sets the name of this File.
        MOUNTAIN_API void SetName(const std::string& newName) override;

        /// @brief Returns the stored Pointer to the Resource loaded from this File.
        ///
        /// Note that a Resource doesn't need to be loaded from a File and can instead be loaded from raw data.
        /// This implies that the return value of this function can be a @c nullptr.
        ATTRIBUTE_NODISCARD
        MOUNTAIN_API Pointer<Resource> GetResource() const;

    protected:
        void UpdateUtilityValues() override;

    private:
        std::string m_NameNoExtension;
        std::string m_Extension;
        std::string m_PathNoExtension;
        Type m_Type = Type::Unknown;

        int8_t* m_Data = nullptr;
        int64_t m_Size = 0;

        /// Null if the file isn't linked to a specific resource or if it is a font file, in which case it can be loaded into
        /// fonts of different sizes
        Pointer<Resource> m_Resource;

        // We need this in order to set m_Resource from the ResourceManager
        // which is the only class that needs to modify this field
        friend class ResourceManager;
    };
}

// Start of File.inl

namespace Mountain
{
    template <typename T>
    const T* File::GetData() const
    {
        return reinterpret_cast<const T*>(m_Data);
    }

    template <typename T>
    T* File::GetData()
    {
        return reinterpret_cast<T*>(m_Data);
    }
}
