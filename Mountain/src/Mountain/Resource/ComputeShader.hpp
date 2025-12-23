#pragma once

#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Resource/ShaderBase.hpp"

namespace Mountain
{
	class ComputeShader : public ShaderBase
	{
	public:
	    /// @brief Allowed extensions for compute shaders
	    MOUNTAIN_API static constexpr Array FileExtensions
	    {
	        ".comp",
	        ".compute"
	    };

		using ShaderBase::ShaderBase;

		using ShaderBase::SetSourceData;

		/// @brief Loads a single compute shader file
		/// @param shader File
		/// @return Whether the load succeeded
		MOUNTAIN_API bool SetSourceData(const Pointer<File>& shader) override;

		/// @brief Loads raw compute shader code
		/// @param buffer Raw data
		/// @param length Raw data length
		MOUNTAIN_API bool Load(const c8* buffer, s64 length);

		/// @brief Creates the compute shader in OpenGL
		MOUNTAIN_API void Load() override;

		/// @brief Destroys the compute shader in OpenGL
		MOUNTAIN_API void Unload() override;

		/// @brief Unloads the compute shader
		MOUNTAIN_API void ResetSourceData() override;

		MOUNTAIN_API bool Reload(bool reloadInBackend) override;

		MOUNTAIN_API void Dispatch(u32 groupsX = 1, u32 groupsY = 1, u32 groupsZ = 1) const;

	private:
		std::string m_Code;

	    bool CheckCompileError(u32 id) const;  // NOLINT(modernize-use-nodiscard)
	};
}
