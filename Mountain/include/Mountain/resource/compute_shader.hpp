#pragma once

#include <Maths/math.hpp>

#include "Mountain/core.hpp"
#include "Mountain/resource/resource.hpp"
#include "Mountain/utils/color.hpp"

BEGIN_MOUNTAIN

class ComputeShader : public Resource
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

	/// @brief Sets an int (signed, 32 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, int32_t value) const;

	/// @brief Sets a bool (signed, 32 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, bool_t value) const;

	/// @brief Sets a float (32 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, float_t value) const;

	/// @brief Sets a Vector2 (2 floats, 64 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector2& value) const;

	/// @brief Sets a Vector3 (3 floats, 96 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector3& value) const;

	/// @brief Sets a Vector4 (4 floats, 128 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector4& value) const;

	/// @brief Sets a Color (4 floats, 128 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Color& value) const;

	/// @brief Sets a Matrix2 (4 floats, 128 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix2& value) const;

	/// @brief Sets a Matrix3 (9 floats, 288 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix3& value) const;

	/// @brief Sets a Matrix (16 floats, 512 bits) variable in a compute shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix& value) const;

	/// @brief Gets the internal id of the compute shader
	/// @return Id
	[[nodiscard]]
	MOUNTAIN_API uint32_t GetId() const;

	/// @brief Binds the compute shader for use
	MOUNTAIN_API void Use() const;

	/// @brief Unbinds the compute shader
	MOUNTAIN_API void Unuse() const;

private:
	uint32_t m_Id = 0;

	std::string m_Code;

	void CheckCompilationError(uint32_t id);

	void CheckLinkError();

	[[nodiscard]]
	int32_t GetUniformLocation(std::string_view keyName) const;
};

END_MOUNTAIN
