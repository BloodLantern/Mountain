#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include "types.h"

#include "constants/sprite.h"

#include "structs/sprite.h"

struct SpriteGraphics {
    u32 handle;
};

struct SpritePalette {
    u32 handle;
    u32 nbrColumns;
    u32 nbrRows;
};

struct SpriteRenderData {
    f32 yPosition;
    f32 xPosition;
    f32 rotation;
    f32 scaling;
    u16 mosaic;
    u16 blending;
    u8 bgPriority;
    u8 paletteRow;
};

#define SPRITE_BUFFER_SIZE (PSPRITE_END + 150)

extern struct SpriteGraphics gSpritesGraphics[SPRITE_BUFFER_SIZE];
extern struct SpritePalette gSpritesPalettes[SPRITE_BUFFER_SIZE];

void SpriteRendererInitBuffers(void);

void SpriteRendererClear(void);
void SpriteRendererLoadAllSpriteGraphics(void);

struct SpriteGraphics* SpriteRendererGetSpriteGraphics(u8 spriteId);
struct SpritePalette* SpriteRendererGetSpritePalette(u8 spriteId);

struct SpriteGraphics* SpriteRendererLoadGraphics(const char* const fileName, u32 lzCompressed);
struct SpritePalette* SpriteRendererLoadPalette(const char* const fileName);

void SpriteRendererLoadGraphicsFile(struct SpriteGraphics* pGraphics, const char* const fileName, u32 lzCompressed);
void SpriteRendererLoadPaletteFile(struct SpritePalette* pPalette, const char* const fileName);

void SpriteRendererRender(const struct SpriteGraphics* pGraphics, const struct SpritePalette* pPalette, const u16* const pOam, const struct SpriteRenderData* pData);

#endif /* SPRITE_RENDERER_H */
