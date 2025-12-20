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
		using Resource::Resource;

		void Unload() override;

		/// @brief Sets an int (signed, 32 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, s32 value) const;

		/// @brief Sets an uint (unsigned, 32 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, u32 value) const;

		/// @brief Sets a bool (signed, 32 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, bool value) const;

		/// @brief Sets a float (32 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, f32 value) const;

		/// @brief Sets a Vector2 (2 floats, 64 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, Vector2i value) const;

		/// @brief Sets a Vector2 (2 floats, 64 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, Vector2 value) const;

		/// @brief Sets a Vector3 (3 floats, 96 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Vector3& value) const;

		/// @brief Sets a Vector4 (4 floats, 128 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Vector4& value) const;

		/// @brief Sets a Color (4 floats, 128 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Color& value) const;

		/// @brief Sets a Matrix2 (4 floats, 128 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Matrix2& value) const;

		/// @brief Sets a Matrix3 (9 floats, 288 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Matrix3& value) const;

		/// @brief Sets a Matrix (16 floats, 512 bits) variable in the shader
		MOUNTAIN_API void SetUniform(const c8* uniformName, const Matrix& value) const;

		/// @brief Sets an enum (cast to a 32-bit unsigned integer) variable in the shader
		template <Concepts::Enum T>
		void SetUniform(const c8* uniformName, T value) const;

		/// @brief Gets the internal id of the shader
		GETTER(u32, Id, m_Id)

		/// @brief Gets all files that this shader depends on, i.e., that are included in this shader.
		GETTER(const std::unordered_set<std::filesystem::path>&, DependentShaderFiles, m_DependentShaderFiles)

	protected:
		u32 m_Id = 0;

		/// @brief List of files that are included in this shader file
		std::unordered_set<std::filesystem::path> m_DependentShaderFiles;

		mutable std::unordered_map<const c8*, s32> m_UniformLocationCache;

		bool CheckCompileError(u32 id, std::string_view type, const std::string& code) const;  // NOLINT(modernize-use-nodiscard)
		bool CheckLinkError() const;  // NOLINT(modernize-use-nodiscard)

		ATTRIBUTE_NODISCARD
		s32 GetUniformLocation(const c8* uniformName) const;

		static void ReplaceIncludes(std::string& code, const std::filesystem::path& path, std::unordered_set<std::filesystem::path>& replacedFiles);
	};

	template <Concepts::Enum T>
	void ShaderBase::SetUniform(const c8* uniformName, T value) const { SetUniform(uniformName, static_cast<u32>(value)); }
}
