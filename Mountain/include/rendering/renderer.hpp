#pragma once

#include "core.hpp"

#include <stack>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Maths/matrix.hpp>
#include <Maths/vector2i.hpp>

#include "render_target.hpp"
#include "utils/color.hpp"

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

BEGIN_MOUNTAIN

struct MOUNTAIN_API OpenGlVersion
{
    const char_t* glsl = "#version 460";
    int32_t major = 4;
    int32_t minor = 4;
};

class Renderer
{
public:
    MOUNTAIN_API static void PushRenderTarget(RenderTarget& renderTarget);
    MOUNTAIN_API static RenderTarget& PopRenderTarget();

    MOUNTAIN_API static OpenGlVersion& GetOpenGlVersion();

private:
    static inline OpenGlVersion m_GlVersion;
    static inline FT_Library m_Freetype;

    static inline std::stack<RenderTarget*> m_RenderTargets;
    static inline RenderTarget* m_RenderTarget;

    static bool Initialize(const char_t* windowTitle, Vector2i windowSize, bool_t vsync, const OpenGlVersion& glVersion = {});
    static void PreFrame();
    static void PostFrame();
    static void Shutdown();
    
    friend class Draw;
    friend class Font;
    friend class Game;
};

END_MOUNTAIN
