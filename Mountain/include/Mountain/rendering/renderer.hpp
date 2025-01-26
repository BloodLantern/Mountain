#pragma once

#include <chrono>
#include <stack>

#include "Mountain/core.hpp"
#include "Mountain/rendering/render_target.hpp"
#include "Mountain/resource/font.hpp"
#include "Mountain/utils/pointer.hpp"

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

// ReSharper disable once CppInconsistentNaming
struct FT_LibraryRec_;
// ReSharper disable once CppEnforceTypeAliasCodeStyle
// ReSharper disable once CppInconsistentNaming
typedef FT_LibraryRec_* FT_Library;

namespace Mountain
{
    struct OpenGlVersion
    {
        const char_t* glsl = "#version 460";
        int32_t major = 4;
        int32_t minor = 4;
    };

    struct DebugStringData
    {
        std::string str;
        std::chrono::time_point<std::chrono::system_clock> time;
        Color color;
        float_t duration;
    };

    class Renderer
    {
    public:
        MOUNTAIN_API static void PushRenderTarget(RenderTarget& renderTarget);
        MOUNTAIN_API static RenderTarget& PopRenderTarget();
        MOUNTAIN_API static RenderTarget& GetCurrentRenderTarget();
        MOUNTAIN_API static RenderTarget& GetDefaultRenderTarget();

        MOUNTAIN_API static void DebugString(std::string str, float_t duration = 1.f, const Color& color = Color::Magenta());
        MOUNTAIN_API static void DebugString(DebugStringData data);

        MOUNTAIN_API static OpenGlVersion& GetOpenGlVersion();

    private:
        static inline OpenGlVersion m_GlVersion;
        static inline FT_Library m_Freetype;

        static inline std::stack<RenderTarget*> m_RenderTargets;
        static inline RenderTarget* m_RenderTarget;

        static inline Pointer<Font> m_DefaultFont;
        static inline List<DebugStringData> m_DebugStrings;

        static bool Initialize(std::string_view windowTitle, Vector2i windowSize, const OpenGlVersion& glVersion = {});
        static void PreFrame();
        static void PostFrame();
        static void Shutdown();

        friend class Draw;
        friend class Font;
        friend class Game;
    };
}
