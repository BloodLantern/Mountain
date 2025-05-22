export module Mountain:Rendering_GpuVertexArray;

import "Mountain/Core.hpp";

import :Core;

export namespace Mountain::Graphics
{
    /// @brief Low-level interface for OpenGL vertex arrays
    struct MOUNTAIN_API GpuVertexArray
    {
        void Create();

        void Delete();

        /// @brief Shorthand for @code Delete(); Create();@endcode
        void Recreate();

        void SetDebugName(std::string_view name) const;

        [[nodiscard]]
        uint32_t GetId() const;

        [[nodiscard]]
        explicit operator uint32_t() const;

    private:
        uint32_t m_Id = 0;
    };
}
