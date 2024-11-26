#pragma once

#include "Mountain/core.hpp"

#include <array>

#include <Maths/math.hpp>

#include "Mountain/file/file.hpp"
#include "Mountain/resource/resource.hpp"
#include "Mountain/utils/color.hpp"
#include "Mountain/utils/pointer.hpp"

/// @file shader.hpp
/// @brief Defines the Mountain::Shader class

BEGIN_MOUNTAIN

/// @brief Shader type
enum class ShaderType : uint8_t
{
	Vertex,
	Fragment,
	Count
};

ENUM_COUNT(ShaderType)

/// @brief Encapsulates shader code information
struct ShaderCode
{
	/// @brief Pointer to raw code
	std::string code;
	/// @brief Shader type
	ShaderType type;
};

/// @brief Encapsulates a GPU shader
class Shader final : public Resource
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
	static ShaderType FileExtensionToType(const std::string& extension);

	using Resource::Resource;

	using Resource::SetSourceData;

	/// @brief Loads a single shader file
	/// @param shader File
	/// @return Whether the load succeeded
	MOUNTAIN_API bool_t SetSourceData(const Pointer<File>& shader) override;

	/// @brief Loads raw shader code
	/// @param buffer Raw data
	/// @param length Raw data length
	/// @param type Shader type
	MOUNTAIN_API bool_t Load(const char_t* buffer, int64_t length, ShaderType type);

	/// @brief Creates the shader in OpenGL
	MOUNTAIN_API void Load() override;

	/// @brief Destroys the shader in OpenGL
	MOUNTAIN_API void Unload() override;

	/// @brief Unloads the shader
	MOUNTAIN_API void ResetSourceData() override;

	/// @brief Sets an int (signed, 32 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, int32_t value) const;

	/// @brief Sets a bool (signed, 32 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, bool_t value) const;

	/// @brief Sets a float (32 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, float_t value) const;

	/// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector2& value) const;
	
	/// @brief Sets a Vector3 (3 floats, 96 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector3& value) const;
	
	/// @brief Sets a Vector4 (4 floats, 128 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Vector4& value) const;
	
	/// @brief Sets a Color (4 floats, 128 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Color& value) const;

	/// @brief Sets a Matrix2 (4 floats, 128 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix2& value) const;

	/// @brief Sets a Matrix3 (9 floats, 288 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix3& value) const;

	/// @brief Sets a Matrix (16 floats, 512 bits) variable in a shader
	/// @param keyName Variable name
	/// @param value Value
	MOUNTAIN_API void SetUniform(std::string_view keyName, const Matrix& value) const;

	/// @brief Gets the internal id of the shader
	/// @return Id
	[[nodiscard]]
	MOUNTAIN_API uint32_t GetId() const;

	/// @brief Binds the shader for use
	MOUNTAIN_API void Use() const;

	/// @brief Unbinds the shader
	MOUNTAIN_API void Unuse() const;

private:
	uint32_t m_Id = 0;
	
	std::array<Pointer<File>, ShaderTypeCount> m_Files;
	std::array<ShaderCode, ShaderTypeCount> m_Code;

	static uint32_t ShaderTypeToOpenGl(ShaderType shaderType);

	void CheckCompilationError(uint32_t id, ShaderType type);

	void CheckLinkError();

	[[nodiscard]]
	int32_t GetUniformLocation(std::string_view keyName) const;
};

END_MOUNTAIN
