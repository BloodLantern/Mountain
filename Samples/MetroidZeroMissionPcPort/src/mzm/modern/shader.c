#include "modern/shader.h"
#include "glad/glad.h"
#include <stdio.h>

static const char* const sShaderTypeNames[] = {
    [0] = "VERTEX",
    [1] = "FRAGMENT",
    [2] = "PROGRAM",
};

struct Shader gShaders[SHADER_BUFFER_SIZE];

void ShaderLoadCommons(void)
{
    ShaderLoad("shaders/sprite.vs", "shaders/sprite.fs");
}

static void ShaderCheckCompileError(u32 shader, u32 type)
{
    int success;
    char infoLog[1024];
    if (type != 2)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            printf("ERROR::SHADER_COMPILATION_ERROR of type: %s\n %s\n -- --------------------------------------------------- -- \n", sShaderTypeNames[type], infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, sizeof(infoLog), NULL, infoLog);
            printf("ERROR::PROGRAM_LINKING_ERROR of type: %s\n %s\n -- --------------------------------------------------- -- \n", sShaderTypeNames[type], infoLog);
        }
    }
}

struct Shader* ShaderLoad(const char* const vertexFile, const char* const fragmentFile)
{
    for (s32 i = 0; i < SHADER_BUFFER_SIZE; i++)
    {
        struct Shader* pShader = &gShaders[i];

        if (pShader->handle != 0)
            continue;

        u32 vertex = ShaderCompileComponent(GL_VERTEX_SHADER, vertexFile);
        u32 fragment = ShaderCompileComponent(GL_FRAGMENT_SHADER, fragmentFile);

        pShader->handle = glCreateProgram();
        glAttachShader(pShader->handle, vertex);
        glAttachShader(pShader->handle, fragment);
        glLinkProgram(pShader->handle);

        ShaderCheckCompileError(pShader->handle, 2);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return pShader;
    }

    return NULL;
}

u32 ShaderCompileComponent(u32 type, const char* const file)
{
    u32 handle;

    FILE* f;
    fopen_s(&f, file, "r");

    if (!f)
    {
        printf("Couldn't load shader %s\n", file);
        return 0;
    }

    handle = glCreateShader(type);

    fseek(f, 0L, SEEK_END);
    u32 fileSize = ftell(f) + 1;
    fclose(f);

    fopen_s(&f, file, "r");
    char* data = memset(malloc(fileSize), '\0', fileSize);
    fread(data, 1, fileSize-1, f);

    glShaderSource(handle, 1, &data, NULL);
    glCompileShader(handle);

    ShaderCheckCompileError(handle, type == GL_VERTEX_SHADER ? 0 : 1);

    free(data);
    fclose(f);

    return handle;
}

void ShaderUse(const struct Shader* pShader)
{
    if (pShader->handle == 0)
    {
        printf("Trying to use a shader that doesn't exists\n");
        return;
    }
    glUseProgram(pShader->handle);
}

void ShaderSetInt(const struct Shader* pShader, const char* const name, s32 value)
{
    glUniform1i(glGetUniformLocation(pShader->handle, name), value);
}

void ShaderSetFloat(const struct Shader* pShader, const char* const name, f32 value)
{
    glUniform1f(glGetUniformLocation(pShader->handle, name), value);
}

void ShaderSetMatrix4x4(const struct Shader* pShader, const char* const name, u8 transpose, const f32* const values)
{
    glUniformMatrix4fv(glGetUniformLocation(pShader->handle, name), 1, transpose, values);
}
