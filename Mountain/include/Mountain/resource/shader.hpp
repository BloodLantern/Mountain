#pragma once

#include "Mountain/core.hpp"

#include <array>

#include "Mountain/file/file.hpp"
#include "Mountain/rendering/graphics.hpp"
#include "Mountain/resource/shader_base.hpp"
#include "Mountain/utils/pointer.hpp"

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
		MOUNTAIN_API static constexpr std::array VertexFileExtensions
		{
			".vert",
			".vertex",
			".vs"
		};

		/// @brief Allowed extensions for fragment shaders
		MOUNTAIN_API static constexpr std::array FragmentFileExtensions
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
		MOUNTAIN_API std::array<Pointer<File>, Graphics::ShaderTypeCount>& GetFiles();

		[[nodiscard]]
		MOUNTAIN_API const std::array<Pointer<File>, Graphics::ShaderTypeCount>& GetFiles() const;

		[[nodiscard]]
		MOUNTAIN_API std::array<ShaderCode, Graphics::ShaderTypeCount>& GetCode();

		[[nodiscard]]
		MOUNTAIN_API const std::array<ShaderCode, Graphics::ShaderTypeCount>& GetCode() const;

		/// @brief Binds the shader for use
		MOUNTAIN_API void Use() const;

		/// @brief Unbinds the shader
		MOUNTAIN_API void Unuse() const;

	private:
		std::array<Pointer<File>, Graphics::ShaderTypeCount> m_Files;
		std::array<ShaderCode, Graphics::ShaderTypeCount> m_Code;

		void CheckCompilationError(uint32_t id, Graphics::ShaderType type);
	};
}
