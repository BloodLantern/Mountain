#pragma once

#include "Mountain/core.hpp"
#include "Mountain/resource/resource.hpp"
#include "Mountain/utils/color.hpp"

namespace Mountain
{
	class ShaderBase : public Resource
	{
	public:
		using Resource::Resource;

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

	protected:
		uint32_t m_Id = 0;

		void CheckLinkError();

		[[nodiscard]]
		int32_t GetUniformLocation(std::string_view keyName) const;
	};
}
