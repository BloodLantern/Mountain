#pragma once

#include <unordered_set>

#include "Mountain/Core.hpp"
#include "Mountain/Resource/Resource.hpp"
#include "Mountain/Utils/Color.hpp"

namespace Mountain
{
	class ShaderBase : public Resource
	{
	public:
		/// @brief List of files that are included in this shader file
		std::unordered_set<std::filesystem::path> dependentShaderFiles;

		using Resource::Resource;

		/// @brief Sets an int (signed, 32 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, int32_t value) const;

		/// @brief Sets an uint (unsigned, 32 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, uint32_t value) const;

		/// @brief Sets a bool (signed, 32 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, bool_t value) const;

		/// @brief Sets a float (32 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, float_t value) const;

		/// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, Vector2i value) const;

		/// @brief Sets a Vector2 (2 floats, 64 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, Vector2 value) const;

		/// @brief Sets a Vector3 (3 floats, 96 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Vector3& value) const;

		/// @brief Sets a Vector4 (4 floats, 128 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Vector4& value) const;

		/// @brief Sets a Color (4 floats, 128 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Color& value) const;

		/// @brief Sets a Matrix2 (4 floats, 128 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Matrix2& value) const;

		/// @brief Sets a Matrix3 (9 floats, 288 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Matrix3& value) const;

		/// @brief Sets a Matrix (16 floats, 512 bits) variable in a shader
		MOUNTAIN_API void SetUniform(const char_t* uniformName, const Matrix& value) const;

		/// @brief Sets an enum (cast to a 32-bit unsigned integer) variable in a shader
		template <Concepts::Enum T>
		void SetUniform(const char_t* uniformName, T value) const;

		/// @brief Gets the internal id of the shader
		ATTRIBUTE_NODISCARD
		MOUNTAIN_API uint32_t GetId() const;

	protected:
		uint32_t m_Id = 0;

		bool_t CheckCompileError(uint32_t id, std::string_view type, const std::string& code) const;  // NOLINT(modernize-use-nodiscard)
		bool_t CheckLinkError() const;  // NOLINT(modernize-use-nodiscard)

		ATTRIBUTE_NODISCARD
		int32_t GetUniformLocation(const char_t* uniformName) const;

		static void ReplaceIncludes(std::string& code, const std::filesystem::path& path, std::unordered_set<std::filesystem::path>& replacedFiles);
	};

	template <Concepts::Enum T>
	void ShaderBase::SetUniform(const char_t* uniformName, T value) const
	{
		SetUniform(uniformName, static_cast<uint32_t>(value));
	}
}
