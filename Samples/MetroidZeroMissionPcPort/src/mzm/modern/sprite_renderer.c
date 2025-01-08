#include "modern/sprite_renderer.h"
#include "modern/shader.h"
#include "data/samus_sprites_pointers.h"
#include "syscalls.h"
#include "glad/glad.h"

#include <stdio.h>
#include <stdlib.h>

enum OamShape {
    OAM_SHAPE_SQUARE,
    OAM_SHAPE_HORIZONTAL,
    OAM_SHAPE_VERTICAL,

    OAM_SHAPE_END
};

enum OamSize {
    OAM_SIZE_SMALL,
    OAM_SIZE_MEDIUM,
    OAM_SIZE_BIG,
    OAM_SIZE_HUGE,

    OAM_SIZE_END
};

struct SpriteGraphics gSpritesGraphics[SPRITE_BUFFER_SIZE];
struct SpritePalette gSpritesPalettes[SPRITE_BUFFER_SIZE];
u32 gOamShapesVao[OAM_SHAPE_END * OAM_SIZE_END];
u32 gOamShapesVbo[OAM_SHAPE_END * OAM_SIZE_END];

u32 ebo;

static const f32 sOamVertices_8x8[] = {
    // positions          // texture coords
     8.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     8.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -8.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -8.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_16x16[] = {
    // positions          // texture coords
     16.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   .09f, 0.5f, // top right
     16.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   .09f, 0.0f, // bottom right
    -16.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -16.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.5f  // top left 
};

static const f32 sOamVertices_32x32[] = {
    // positions          // texture coords
     32.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     32.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -32.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -32.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_64x64[] = {
    // positions          // texture coords
     64.f / SCREEN_SIZE_X,  64.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     64.f / SCREEN_SIZE_X, -64.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -64.f / SCREEN_SIZE_X, -64.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -64.f / SCREEN_SIZE_X,  64.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};


static const f32 sOamVertices_16x8[] = {
    // positions          // texture coords
     16.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     16.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -16.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -16.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_32x8[] = {
    // positions          // texture coords
     32.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     32.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -32.f / SCREEN_SIZE_X, -8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -32.f / SCREEN_SIZE_X,  8.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_32x16[] = {
    // positions          // texture coords
     32.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     32.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -32.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -32.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_64x32[] = {
    // positions          // texture coords
     64.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     64.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -64.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -64.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};


static const f32 sOamVertices_8x16[] = {
    // positions          // texture coords
     8.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     8.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -8.f / SCREEN_SIZE_X, -16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -8.f / SCREEN_SIZE_X,  16.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_8x32[] = {
    // positions          // texture coords
     8.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     8.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -8.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -8.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_16x32[] = {
    // positions          // texture coords
     16.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     16.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -16.f / SCREEN_SIZE_X, -32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -16.f / SCREEN_SIZE_X,  32.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32 sOamVertices_32x64[] = {
    // positions          // texture coords
     32.f / SCREEN_SIZE_X,  64.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 1.0f, // top right
     32.f / SCREEN_SIZE_X, -64.f / SCREEN_SIZE_Y, 0.0f,   1.0f, 0.0f, // bottom right
    -32.f / SCREEN_SIZE_X, -64.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 0.0f, // bottom left
    -32.f / SCREEN_SIZE_X,  64.f / SCREEN_SIZE_Y, 0.0f,   0.0f, 1.0f  // top left 
};

static const f32* const sOamShapesVertices[OAM_SHAPE_END][OAM_SIZE_END] = {
    [OAM_SHAPE_SQUARE] = {
        [OAM_SIZE_SMALL] = sOamVertices_8x8,
        [OAM_SIZE_MEDIUM] = sOamVertices_16x16,
        [OAM_SIZE_BIG] = sOamVertices_32x32,
        [OAM_SIZE_HUGE] = sOamVertices_64x64,
    },
    [OAM_SHAPE_HORIZONTAL] = {
        [OAM_SIZE_SMALL] = sOamVertices_16x8,
        [OAM_SIZE_MEDIUM] = sOamVertices_32x8,
        [OAM_SIZE_BIG] = sOamVertices_32x16,
        [OAM_SIZE_HUGE] = sOamVertices_64x32,
    },
    [OAM_SHAPE_VERTICAL] = {
        [OAM_SIZE_SMALL] = sOamVertices_8x16,
        [OAM_SIZE_MEDIUM] = sOamVertices_8x32,
        [OAM_SIZE_BIG] = sOamVertices_16x32,
        [OAM_SIZE_HUGE] = sOamVertices_32x64,
    },
};

void SpriteRendererInitBuffers(void)
{
    u32 indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(ARRAY_SIZE(gOamShapesVao), gOamShapesVao);
    glGenBuffers(ARRAY_SIZE(gOamShapesVbo), gOamShapesVbo);

    glGenBuffers(1, &ebo);

    for (s32 i = 0; i < OAM_SHAPE_END; i++)
    {
        for (s32 j = 0; j < OAM_SIZE_END; j++)
        {
            glBindVertexArray(gOamShapesVao[i * OAM_SIZE_END + j]);

            glBindBuffer(GL_ARRAY_BUFFER, gOamShapesVbo[i * OAM_SIZE_END + j]);
            glBufferData(GL_ARRAY_BUFFER, 5 * 4 * sizeof(f32), sOamShapesVertices[i][j], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            // texture coord attribute
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }
}

void SpriteRendererClear(void)
{
    for (s32 i = 0; i < SPRITE_BUFFER_SIZE; i++)
    {
        struct SpriteGraphics* pGraphics = &gSpritesGraphics[i];
        struct SpritePalette* pPalette = &gSpritesPalettes[i];

        if (pGraphics->handle != 0)
        {
            glDeleteTextures(1, &pGraphics->handle);
            pGraphics->handle = 0;
        }

        if (pPalette->handle != 0)
        {
            glDeleteTextures(1, &pGraphics->handle);
            pPalette->handle = 0;
        }
    }
}

void SpriteRendererLoadAllSpriteGraphics(void)
{
    SpriteRendererClear();
    for (s32 i = 0; i < PSPRITE_END; i++)
    {
        if (sSpritesGraphicsFilePointers[i] == NULL)
            continue;

        struct SpriteGraphics* pGraphics = &gSpritesGraphics[i];
        struct SpritePalette* pPalette = &gSpritesPalettes[i];

        glGenTextures(1, &pGraphics->handle);
        SpriteRendererLoadGraphicsFile(pGraphics, sSpritesGraphicsFilePointers[i], TRUE);
        glGenTextures(1, &pPalette->handle);
        SpriteRendererLoadPaletteFile(pPalette, sSpritesPalettesFilePointers[i]);
    }
}

struct SpriteGraphics* SpriteRendererGetSpriteGraphics(u8 spriteId)
{
    return &gSpritesGraphics[spriteId];
}

struct SpritePalette* SpriteRendererGetSpritePalette(u8 spriteId)
{
    return &gSpritesPalettes[spriteId];
}

struct SpriteGraphics* SpriteRendererLoadGraphics(const char* const fileName, u32 lzCompressed)
{
    if (fileName == NULL)
        return NULL;

    for (s32 i = 0; i < SPRITE_BUFFER_SIZE; i++)
    {
        struct SpriteGraphics* pGraphics = &gSpritesGraphics[i];

        if (pGraphics->handle != 0)
            continue;

        glGenTextures(1, &pGraphics->handle);
        // printf("Generated graphics : %d\n", pGraphics->handle);

        SpriteRendererLoadGraphicsFile(pGraphics, fileName, lzCompressed);

        return pGraphics;
    }

    return NULL;
}

struct SpritePalette* SpriteRendererLoadPalette(const char* const fileName)
{
    if (fileName == NULL)
        return NULL;

    for (s32 i = 0; i < SPRITE_BUFFER_SIZE; i++)
    {
        struct SpritePalette* pPalette = &gSpritesPalettes[i];

        if (pPalette->handle != 0)
            continue;

        glGenTextures(1, &pPalette->handle);
        // printf("Generated palette : %d\n", pPalette->handle);

        SpriteRendererLoadPaletteFile(pPalette, fileName);

        return pPalette;
    }

    return NULL;
}

void SpriteRendererLoadGraphicsFile(struct SpriteGraphics* pGraphics, const char* const fileName, u32 lzCompressed)
{
    if (fileName == NULL)
        return;

    FILE* f;
    fopen_s(&f, fileName, "rb");

    if (!f)
    {
        printf("Couldn't open graphics file : %s\n", fileName);
        return;
    }

    fseek(f, 0, SEEK_END);
    u32 fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    u32* data = malloc(fileSize);
    fread(data, fileSize, 1, f);

    u32 decompSize = *data >> 8;

    u8* decomp;
    if (lzCompressed)
    {
        decomp = malloc(decompSize);
        LZ77UncompVRAM(data, decomp);
    }
    else
    {
        decomp = (u8*)data;
        decompSize = fileSize;
    }

    u8* convertedData = malloc(decompSize * 2);

    for (s32 i = 0; i < decompSize; i++)
    {
        u8 value = decomp[i];
        u8 low = value & 0b1111;
        u8 high = (value >> 4) & 0b1111;

        s32 currSquare = i / 32;
        s32 squareX = currSquare % 32;
        s32 squareY = currSquare / 32;
        s32 currLine = (i - currSquare * 32) / 4 % 8;
        s32 currColumn = (i - currSquare * 32) % 4;

        s32 idx = squareX * 4 + squareY * 1024 + currLine * 128 + currColumn;

        // printf("%d ; %d ; %d\n", i, currSquare, idx);
        // printf("%d ; %d ; %d ; %d ; %d ; %x\n", i, currSquare, currLine, currColumn, idx, value);

        if (idx >= decompSize)
        {
            // printf("OOB when trying to convert graphics : %d\n", idx);
            idx = decompSize - 1;
        }

        convertedData[idx * 2 + 0] = (float)low / 15 * UCHAR_MAX;
        convertedData[idx * 2 + 1] = (float)high / 15 * UCHAR_MAX;
    }

    glBindTexture(GL_TEXTURE_2D, pGraphics->handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, 256, decompSize / 0x400 * 8, 0, GL_RED, GL_UNSIGNED_BYTE, convertedData);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(data);
    if (lzCompressed)
        free(decomp);
    free(convertedData);
    fclose(f);
}

void SpriteRendererLoadPaletteFile(struct SpritePalette* pPalette, const char* const fileName)
{
    if (fileName == NULL)
        return;

    FILE* f;
    fopen_s(&f, fileName, "rb");

    if (!f)
    {
        printf("Couldn't open palette file : %s\n", fileName);
        return;
    }

    fseek(f, 0, SEEK_END);
    u32 size = ftell(f);
    fseek(f, 0, SEEK_SET);

    pPalette->nbrColumns = 16;
    pPalette->nbrRows = size / 16 / 2;

    u32 nbrColors = size / 2;

    u16* data = malloc(size);

    fread(data, size, 1, f);
    u8* convertedData = malloc(nbrColors * 3);

    for (s32 i = 0; i < nbrColors; i++)
    {
        u16 color = data[i];
        u16 r = RED(color);
        u16 g = GREEN(color);
        u16 b = BLUE(color);

        convertedData[i * 3 + 0] = (u8)(((float)r / COLOR_MASK) * UCHAR_MAX);
        convertedData[i * 3 + 1] = (u8)(((float)g / COLOR_MASK) * UCHAR_MAX);
        convertedData[i * 3 + 2] = (u8)(((float)b / COLOR_MASK) * UCHAR_MAX);
    }

    glBindTexture(GL_TEXTURE_2D, pPalette->handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    u32 rows = nbrColors / 16;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 16, rows, 0, GL_RGB, GL_UNSIGNED_BYTE, convertedData);

    glBindTexture(GL_TEXTURE_2D, 0);

    free(data);
    free(convertedData);
    fclose(f);
}

void SpriteRendererRender(const struct SpriteGraphics* pGraphics, const struct SpritePalette* pPalette, const u16* const pOam, const struct SpriteRenderData* pData)
{
    if (pGraphics == NULL || pGraphics->handle == 0)
    {
        printf("Trying to render with no graphics\n");
        return;
    }

    if (pPalette == NULL || pPalette->handle == 0)
    {
        printf("Trying to render with no palette\n");
        return;
    }

    if (pOam == NULL)
    {
        printf("Trying to render without oam\n");
        return;
    }
    
    if (pData == NULL)
    {
        printf("Trying to render without draw data\n");
        return;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, pGraphics->handle);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pPalette->handle);

    struct Shader* pShader = &gShaders[0];

    ShaderUse(pShader);
    ShaderSetInt(pShader, "graphics", 0);
    ShaderSetInt(pShader, "palette", 1);

    f32 paletteV = (f32)pData->paletteRow / pPalette->nbrRows;
    ShaderSetFloat(pShader, "paletteRow", paletteV);

    const f32 transformMatrix[] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };

    ShaderSetMatrix4x4(pShader, "transform", TRUE, transformMatrix);

    glBindVertexArray(gOamShapesVao[OAM_SHAPE_SQUARE * OAM_SIZE_END + OAM_SIZE_HUGE]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
