#ifndef SHADER_H
#define SHADER_H

#include "types.h"

struct Shader {
    u32 handle;
};

#define SHADER_BUFFER_SIZE 20

extern struct Shader gShaders[SHADER_BUFFER_SIZE];

void ShaderLoadCommons(void);
struct Shader* ShaderLoad(const char* const vertexFile, const char* const fragmentFile);
u32 ShaderCompileComponent(u32 type, const char* const file);

void ShaderUse(const struct Shader* pShader);
void ShaderSetInt(const struct Shader* pShader, const char* const name, s32 value);
void ShaderSetFloat(const struct Shader* pShader, const char* const name, f32 value);
void ShaderSetMatrix4x4(const struct Shader* pShader, const char* const name, u8 transpose, const f32* const values);

#endif /* SHADER_H */
