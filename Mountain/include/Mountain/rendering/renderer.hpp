#pragma once

#include "Mountain/core.hpp"

#include <stack>

#include "Mountain/rendering/render_target.hpp"

// ReSharper disable once CppInconsistentNaming
struct GLFWwindow;

// ReSharper disable once CppInconsistentNaming
struct FT_LibraryRec_;
// ReSharper disable once CppEnforceTypeAliasCodeStyle
// ReSharper disable once CppInconsistentNaming
typedef FT_LibraryRec_* FT_Library;

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
    MOUNTAIN_API static RenderTarget& GetCurrentRenderTarget();

    MOUNTAIN_API static OpenGlVersion& GetOpenGlVersion();

private:
    static inline OpenGlVersion m_GlVersion;
    static inline FT_Library m_Freetype;

    static inline std::stack<RenderTarget*> m_RenderTargets;
    static inline RenderTarget* m_RenderTarget;

    static bool Initialize(std::string_view windowTitle, Vector2i windowSize, bool_t vsync, const OpenGlVersion& glVersion = {});
    static void PreFrame();
    static void PostFrame();
    static void Shutdown();
    
    friend class Draw; // TODO - Change these to friend functions instead
    friend class Font;
    friend class Game;
};

END_MOUNTAIN
