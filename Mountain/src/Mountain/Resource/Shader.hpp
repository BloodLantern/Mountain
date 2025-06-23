#pragma once

#include "Mountain/Core.hpp"

#include <array>

#include "Mountain/FileSystem/File.hpp"
#include "Mountain/Rendering/Graphics.hpp"
#include "Mountain/Resource/ShaderBase.hpp"
#include "Mountain/Utils/Pointer.hpp"

/// @file shader.hpp
/// @brief Defines the Mountain::Shader class

namespace Mountain
{
	/// @brief Encapsulates shader code information
	struct ShaderCode
	{
		/// @brief Pointer to raw code
		std::string code;
		/// @brief Shader type
		Graphics::ShaderType type;
	};

	/// @brief Encapsulates a GPU shader
	class Shader final : public ShaderBase
	{
	public:
		/// @brief Allowed extensions for vertex shaders
		MOUNTAIN_API static constexpr Array VertexFileExtensions
		{
			".vert",
			".vertex",
			".vs"
		};

		/// @brief Allowed extensions for fragment shaders
		MOUNTAIN_API static constexpr Array FragmentFileExtensions
		{
			".frag",
			".fragment",
			".fs"
		};

		/// @brief Gets the shader type via a file extension
		/// @param extension File extension
		/// @return @ref ShaderType type
		/// @throw std::invalid_argument If the extension isn't valid
		[[nodiscard]]
		static Graphics::ShaderType FileExtensionToType(const std::string& extension);

		using ShaderBase::ShaderBase;

		using ShaderBase::SetSourceData;

		/// @brief Loads a single shader file
		/// @param shader File
		/// @return Whether the load succeeded
		MOUNTAIN_API bool_t SetSourceData(const Pointer<File>& shader) override;

		/// @brief Loads raw shader code
		/// @param buffer Raw data
		/// @param length Raw data length
		/// @param type Shader type
		MOUNTAIN_API bool_t Load(const char_t* buffer, int64_t length, Graphics::ShaderType type);

		/// @brief Creates the shader in OpenGL
		MOUNTAIN_API void Load() override;

		/// @brief Destroys the shader in OpenGL
		MOUNTAIN_API void Unload() override;

		/// @brief Unloads the shader
		MOUNTAIN_API void ResetSourceData() override;

		MOUNTAIN_API bool_t Reload(bool_t reloadInBackend = true) override;

		MOUNTAIN_API bool_t Reload(const Pointer<File>& file, bool_t reloadInBackend = true) override;

		[[nodiscard]]
		MOUNTAIN_API Array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& GetFiles();

		[[nodiscard]]
		MOUNTAIN_API const Array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()>& GetFiles() const;

		[[nodiscard]]
		MOUNTAIN_API Array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& GetCode();

		[[nodiscard]]
		MOUNTAIN_API const Array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()>& GetCode() const;

		/// @brief Binds the shader for use
		MOUNTAIN_API void Use() const;

		/// @brief Unbinds the shader
		MOUNTAIN_API void Unuse() const;

	private:
		Array<Pointer<File>, magic_enum::enum_count<Graphics::ShaderType>()> m_Files;
		Array<ShaderCode, magic_enum::enum_count<Graphics::ShaderType>()> m_Code;

		bool_t CheckCompileError(uint32_t id, Graphics::ShaderType type) const;  // NOLINT(modernize-use-nodiscard)
	};
}
