#pragma once

#include <Maths/math.hpp>

#include "Mountain/core.hpp"
#include "Mountain/resource/shader_base.hpp"

BEGIN_MOUNTAIN

class ComputeShader : public ShaderBase
{
public:
    /// @brief Allowed extensions for compute shaders
    MOUNTAIN_API static constexpr std::array FileExtensions
    {
        ".comp",
        ".compute"
    };

	using Resource::Resource;

	using Resource::SetSourceData;

	/// @brief Loads a single compute shader file
	/// @param shader File
	/// @return Whether the load succeeded
	MOUNTAIN_API bool_t SetSourceData(const Pointer<File>& shader) override;

	/// @brief Loads raw compute shader code
	/// @param buffer Raw data
	/// @param length Raw data length
	MOUNTAIN_API bool_t Load(const char_t* buffer, int64_t length);

	/// @brief Creates the compute shader in OpenGL
	MOUNTAIN_API void Load() override;

	/// @brief Destroys the compute shader in OpenGL
	MOUNTAIN_API void Unload() override;

	/// @brief Unloads the compute shader
	MOUNTAIN_API void ResetSourceData() override;

	MOUNTAIN_API void Dispatch(uint32_t groupsX, uint32_t groupsY, uint32_t groupsZ) const;

	MOUNTAIN_API void SynchronizeImageData() const;

private:
	std::string m_Code;

	void CheckCompilationError(uint32_t id);
};

END_MOUNTAIN
