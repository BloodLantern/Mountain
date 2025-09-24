#include "Mountain/PrecompiledHeader.hpp"

#include "Mountain/Graphics/Graphics.hpp"

#include <glad/glad.h>

#include "Mountain/Exceptions/ArgumentException.hpp"
#include "Mountain/Exceptions/ThrowHelper.hpp"
#include "Mountain/Graphics/GpuBuffer.hpp"
#include "Mountain/Graphics/GpuFramebuffer.hpp"
#include "Mountain/Graphics/GpuTexture.hpp"
#include "Mountain/Graphics/GpuVertexArray.hpp"
#include "Mountain/Utils/Utils.hpp"

using namespace Mountain;

void Graphics::BindImage(const uint32_t textureId, const uint32_t shaderBinding, const ImageShaderAccess access)
{
    glBindImageTexture(shaderBinding, textureId, 0, GL_FALSE, 0, GL_READ_ONLY + static_cast<int32_t>(access), GL_RGBA32F);
}

void Graphics::SetActiveTexture(const uint8_t activeTexture)
{
    glActiveTexture(GL_TEXTURE0 + activeTexture);
}

void Graphics::SynchronizeGpuData(const GpuDataSynchronizationFlags flags) { glMemoryBarrier(static_cast<GLbitfield>(flags)); }

void Graphics::MemoryBarrier(const MemoryBarrierFlags flags) { glMemoryBarrier(static_cast<GLbitfield>(flags)); }

void Graphics::DrawArrays(const DrawMode mode, const int32_t first, const int32_t vertexCount)
{
    glDrawArrays(ToOpenGl(mode), first, vertexCount);
}

void Graphics::DrawArraysInstanced(const DrawMode mode, const int32_t first, const int32_t vertexCount, const int32_t instanceCount)
{
    glDrawArraysInstanced(ToOpenGl(mode), first, vertexCount, instanceCount);
}

void Graphics::DrawElements(const DrawMode mode, const int32_t vertexCount, const DataType type, const void* indices)
{
    glDrawElements(ToOpenGl(mode), vertexCount, ToOpenGl(type), indices);
}

void Graphics::DrawElementsInstanced(
    const DrawMode mode,
    const int32_t vertexCount,
    const DataType type,
    const void* indices,
    const int32_t instanceCount
)
{
    glDrawElementsInstanced(ToOpenGl(mode), vertexCount, ToOpenGl(type), indices, instanceCount);
}

void Graphics::SetClearColor(const Color& newClearColor)
{
    glClearColor(newClearColor.r, newClearColor.g, newClearColor.b, newClearColor.a); // FIXME - This seems to be broken since we switched to SDL3
}

void Graphics::Clear(const ClearFlags flags)
{
    glClear(static_cast<GLbitfield>(flags));
}

void Graphics::BindTexture(const uint32_t textureId) { glBindTexture(GL_TEXTURE_2D, textureId); }

void Graphics::BindTexture(const GpuTexture gpuTexture) { BindTexture(gpuTexture.GetId()); }

void Graphics::BindBuffer(const BufferType type, const uint32_t bufferId) { glBindBuffer(ToOpenGl(type), bufferId); }

void Graphics::BindBuffer(const BufferType type, const GpuBuffer gpuBuffer) { BindBuffer(type, gpuBuffer.GetId()); }

void Graphics::BindBufferBase(const BufferType type, const uint32_t index, const GpuBuffer gpuBuffer)
{
    BindBufferBase(type, index, gpuBuffer.GetId());
}

void Graphics::BindBufferBase(const BufferType type, const uint32_t index, const uint32_t bufferId)
{
    glBindBufferBase(ToOpenGl(type), index, bufferId);
}

void Graphics::BindVertexArray(const uint32_t vertexArrayId) { glBindVertexArray(vertexArrayId); }

void Graphics::BindVertexArray(const GpuVertexArray gpuVertexArray) { BindVertexArray(gpuVertexArray.GetId()); }

void Graphics::SetVertexAttribute(
    const uint32_t index,
    const int32_t size,
    const int32_t stride,
    const size_t offset,
    const uint32_t divisor
)
{
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, Utils::IntToPointer<void>(offset));
    glEnableVertexAttribArray(index);
    if (divisor != 0)
        glVertexBindingDivisor(index, divisor);
}

void Graphics::SetVertexAttributeInt(
    const uint32_t index,
    const int32_t size,
    const int32_t stride,
    const size_t offset,
    const uint32_t divisor
)
{
    glVertexAttribIPointer(index, size, GL_INT, stride, Utils::IntToPointer<void>(offset));
    glEnableVertexAttribArray(index);
    if (divisor != 0)
        glVertexBindingDivisor(index, divisor);
}

void Graphics::BindFramebuffer(const FramebufferType type, const uint32_t framebufferId) { glBindFramebuffer(ToOpenGl(type), framebufferId); }

void Graphics::BindFramebuffer(const FramebufferType type, const GpuFramebuffer gpuFramebuffer) { BindFramebuffer(type, gpuFramebuffer.GetId()); }

void Graphics::CopyTextureData(
    const uint32_t sourceTextureId,
    const int32_t sourceMipmapLevel,
    const Vector2i sourceOffset,
    const uint32_t destinationTextureId,
    const int32_t destinationMipmapLevel,
    const Vector2i destinationOffset,
    const Vector2i size
)
{
    glCopyImageSubData(
        sourceTextureId,
        GL_TEXTURE_2D,
        sourceMipmapLevel,
        sourceOffset.x,
        sourceOffset.y,
        0,
        destinationTextureId,
        GL_TEXTURE_2D,
        destinationMipmapLevel,
        destinationOffset.x,
        destinationOffset.y,
        0,
        size.x,
        size.y,
        1
    );
}

int32_t Graphics::GetProgramUniformLocation(const uint32_t shaderProgramId, const char_t* uniformName) { return glGetUniformLocation(shaderProgramId, uniformName); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const int32_t value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const uint32_t value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const bool_t value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const float_t value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Vector2i value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Vector2 value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Vector3& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Vector4& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Color& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Matrix2& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Matrix3& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const char_t* uniformName, const Matrix& value) { SetProgramUniform(shaderProgramId, GetProgramUniformLocation(shaderProgramId, uniformName), value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const int32_t value) { glProgramUniform1i(shaderProgramId, uniformLocation, value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const uint32_t value) { glProgramUniform1ui(shaderProgramId, uniformLocation, value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const bool_t value) { SetProgramUniform(shaderProgramId, uniformLocation, static_cast<int32_t>(value)); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const float_t value) { glProgramUniform1f(shaderProgramId, uniformLocation, value); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Vector2i value) { glProgramUniform2iv(shaderProgramId, uniformLocation, 1, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Vector2 value) { glProgramUniform2fv(shaderProgramId, uniformLocation, 1, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Vector3& value) { glProgramUniform3fv(shaderProgramId, uniformLocation, 1, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Vector4& value) { glProgramUniform4fv(shaderProgramId, uniformLocation, 1, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Color& value) { SetProgramUniform(shaderProgramId, uniformLocation, value.ToVector4()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Matrix2& value) { glProgramUniformMatrix2fv(shaderProgramId, uniformLocation, 1, GL_FALSE, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Matrix3& value) { glProgramUniformMatrix3fv(shaderProgramId, uniformLocation, 1, GL_FALSE, value.Data()); }

void Graphics::SetProgramUniform(const uint32_t shaderProgramId, const int32_t uniformLocation, const Matrix& value) { glProgramUniformMatrix4fv(shaderProgramId, uniformLocation, 1, GL_FALSE, value.Data()); }

void Graphics::SetViewport(const Vector2i position, const Vector2i size)
{
    glViewport(position.x, position.y, size.x, size.y);
}

uint32_t Graphics::GetLastError() { return glGetError(); }

const char_t* Graphics::GetLastErrorString() { return reinterpret_cast<const char_t*>(glGetString(glGetError())); }

bool_t Graphics::IsConstantEnabled(const Constant constant) { return glIsEnabled(ToOpenGl(constant)); }

bool_t Graphics::IsConstantEnabled(const Constant constant, const uint32_t index) { return glIsEnabledi(ToOpenGl(constant), index); }

void Graphics::GetConstant(const Constant constant, bool_t* outData) { glGetBooleanv(ToOpenGl(constant), reinterpret_cast<GLboolean*>(outData)); }

void Graphics::GetConstant(const Constant constant, double_t* outData) { glGetDoublev(ToOpenGl(constant), outData); }

void Graphics::GetConstant(const Constant constant, float_t* outData) { glGetFloatv(ToOpenGl(constant), outData); }

void Graphics::GetConstant(const Constant constant, int32_t* outData) { glGetIntegerv(ToOpenGl(constant), outData); }

void Graphics::GetConstant(const Constant constant, int64_t* outData) { glGetInteger64v(ToOpenGl(constant), outData); }

void Graphics::GetConstant(const Constant constant, const uint32_t index, bool_t* outData) { glGetBooleani_v(ToOpenGl(constant), index, reinterpret_cast<GLboolean*>(outData)); }

void Graphics::GetConstant(const Constant constant, const uint32_t index, double_t* outData) { glGetDoublei_v(ToOpenGl(constant), index, outData); }

void Graphics::GetConstant(const Constant constant, const uint32_t index, float_t* outData) { glGetFloati_v(ToOpenGl(constant), index, outData); }

void Graphics::GetConstant(const Constant constant, const uint32_t index, int32_t* outData) { glGetIntegeri_v(ToOpenGl(constant), index, outData); }

void Graphics::GetConstant(const Constant constant, const uint32_t index, int64_t* outData) { glGetInteger64i_v(ToOpenGl(constant), index, outData); }

void Graphics::SetConstantEnabled(const Constant constant, const bool_t enabled)
{
    if (enabled)
        EnableConstant(constant);
    else
        DisableConstant(constant);
}

void Graphics::SetConstantEnabled(const Constant constant, const uint32_t index, const bool_t enabled)
{
    if (enabled)
        EnableConstant(constant, index);
    else
        DisableConstant(constant, index);
}

void Graphics::EnableConstant(const Constant constant) { glEnable(ToOpenGl(constant)); }

void Graphics::EnableConstant(const Constant constant, const uint32_t index) { glEnablei(ToOpenGl(constant), index); }

void Graphics::DisableConstant(const Constant constant) { glDisable(ToOpenGl(constant)); }

void Graphics::DisableConstant(const Constant constant, const uint32_t index) { glDisablei(ToOpenGl(constant), index); }

void Graphics::SetBlendFunction(const BlendFunction sourceFactors, const BlendFunction destinationFactors)
{
    glBlendFunc(ToOpenGl(sourceFactors), ToOpenGl(destinationFactors));
}

void Graphics::SetBlendFunction(const uint32_t drawBuffer, const BlendFunction sourceFactors, const BlendFunction destinationFactors)
{
    glBlendFunci(drawBuffer, ToOpenGl(sourceFactors), ToOpenGl(destinationFactors));
}

void Graphics::SetViewport(const int32_t x, const int32_t y, const int32_t width, const int32_t height) { glViewport(x, y, width, height); }

void Graphics::Flush()
{
    glFlush();
}

void Graphics::Finish()
{
    glFinish();
}

template <>
Graphics::MagnificationFilter Graphics::FromOpenGl<Graphics::MagnificationFilter>(const int32_t value)
{
    switch (value)
    {
        case GL_NEAREST: return MagnificationFilter::Nearest;
        case GL_LINEAR: return MagnificationFilter::Linear;

        default: THROW(ArgumentOutOfRangeException{"Invalid magnification filter", "value"});
    }
}

template <>
Graphics::Wrapping Graphics::FromOpenGl<Graphics::Wrapping>(const int32_t value)
{
    switch (value)
    {
        case GL_REPEAT: return Wrapping::Repeat;
        case GL_MIRRORED_REPEAT: return Wrapping::MirroredRepeat;
        case GL_CLAMP_TO_EDGE: return Wrapping::ClampToEdge;
        case GL_CLAMP_TO_BORDER: return Wrapping::ClampToBorder;

        default: THROW(ArgumentOutOfRangeException{"Invalid wrapping", "value"});
    }
}

template <>
Graphics::ShaderType Graphics::FromOpenGl<Graphics::ShaderType>(const int32_t value)
{
    switch (value)
    {
        case GL_VERTEX_SHADER: return ShaderType::Vertex;
        case GL_FRAGMENT_SHADER: return ShaderType::Fragment;
        case GL_GEOMETRY_SHADER: return ShaderType::Geometry;

        default: THROW(ArgumentOutOfRangeException{"Invalid shader type", "value"});
    }
}

template <>
Graphics::InternalFormat Graphics::FromOpenGl<Graphics::InternalFormat>(const int32_t value)
{
    switch (value)
    {
        case GL_DEPTH_COMPONENT: return InternalFormat::DepthComponent;
        case GL_DEPTH_STENCIL: return InternalFormat::DepthStencil;
        case GL_RED: return InternalFormat::Red;
        case GL_RG: return InternalFormat::RedGreen;
        case GL_RGB: return InternalFormat::RedGreenBlue;
        case GL_RGBA: return InternalFormat::RedGreenBlueAlpha;

        case GL_DEPTH_COMPONENT16: return InternalFormat::DepthComponent16;
        case GL_DEPTH_COMPONENT24: return InternalFormat::DepthComponent24;
        case GL_DEPTH_COMPONENT32F: return InternalFormat::DepthComponent32Float;
        case GL_R8: return InternalFormat::Red8;
        case GL_R8_SNORM: return InternalFormat::Red8Signed;
        case GL_R16: return InternalFormat::Red16;
        case GL_R16_SNORM: return InternalFormat::Red16Signed;
        case GL_RG8: return InternalFormat::RedGreen8;
        case GL_RG8_SNORM: return InternalFormat::RedGreen8Signed;
        case GL_RG16: return InternalFormat::RedGreen16;
        case GL_RG16_SNORM: return InternalFormat::RedGreen16Signed;
        case GL_R3_G3_B2: return InternalFormat::Red3Green3Blue2;
        case GL_RGB4: return InternalFormat::RedGreenBlue4;
        case GL_RGB5: return InternalFormat::RedGreenBlue5;
        case GL_RGB8: return InternalFormat::RedGreenBlue8;
        case GL_RGB8_SNORM: return InternalFormat::RedGreenBlue8Signed;
        case GL_RGB10: return InternalFormat::RedGreenBlue10;
        case GL_RGB12: return InternalFormat::RedGreenBlue12;
        case GL_RGB16: return InternalFormat::RedGreenBlue16;
        case GL_RGB16_SNORM: return InternalFormat::RedGreenBlue16Signed;
        case GL_RGBA2: return InternalFormat::RedGreenBlueAlpha2;
        case GL_RGBA4: return InternalFormat::RedGreenBlueAlpha4;
        case GL_RGB5_A1: return InternalFormat::RedGreenBlue5Alpha1;
        case GL_RGBA8: return InternalFormat::RedGreenBlueAlpha8;
        case GL_RGBA8_SNORM: return InternalFormat::RedGreenBlueAlpha8Signed;
        case GL_RGB10_A2: return InternalFormat::RedGreenBlue10Alpha2;
        case GL_RGB10_A2UI: return InternalFormat::RedGreenBlue10Alpha2UnsignedInt;
        case GL_RGBA12: return InternalFormat::RedGreenBlueAlpha12;
        case GL_RGBA16: return InternalFormat::RedGreenBlueAlpha16;
        case GL_SRGB8: return InternalFormat::SignedRedGreenBlue8;
        case GL_SRGB8_ALPHA8: return InternalFormat::SignedRedGreenBlueAlpha8;
        case GL_R16F: return InternalFormat::Red16Float;
        case GL_RG16F: return InternalFormat::RedGreen16Float;
        case GL_RGB16F: return InternalFormat::RedGreenBlue16Float;
        case GL_RGBA16F: return InternalFormat::RedGreenBlueAlpha16Float;
        case GL_R32F: return InternalFormat::Red32Float;
        case GL_RG32F: return InternalFormat::RedGreen32Float;
        case GL_RGB32F: return InternalFormat::RedGreenBlue32Float;
        case GL_RGBA32F: return InternalFormat::RedGreenBlueAlpha32Float;
        case GL_R11F_G11F_B10F: return InternalFormat::Red11FloatGreen11FloatBlue10Float;
        case GL_RGB9_E5: return InternalFormat::RedGreenBlue9Shared5;
        case GL_R8I: return InternalFormat::Red8Int;
        case GL_R8UI: return InternalFormat::Red8UnsignedInt;
        case GL_R16I: return InternalFormat::Red16Int;
        case GL_R16UI: return InternalFormat::Red16UnsignedInt;
        case GL_R32I: return InternalFormat::Red32Int;
        case GL_R32UI: return InternalFormat::Red32UnsignedInt;
        case GL_RG8I: return InternalFormat::RedGreen8Int;
        case GL_RG8UI: return InternalFormat::RedGreen8UnsignedInt;
        case GL_RG16I: return InternalFormat::RedGreen16Int;
        case GL_RG16UI: return InternalFormat::RedGreen16UnsignedInt;
        case GL_RG32I: return InternalFormat::RedGreen32Int;
        case GL_RG32UI: return InternalFormat::RedGreen32UnsignedInt;
        case GL_RGB8I: return InternalFormat::RedGreenBlue8Int;
        case GL_RGB8UI: return InternalFormat::RedGreenBlue8UnsignedInt;
        case GL_RGB16I: return InternalFormat::RedGreenBlue16Int;
        case GL_RGB16UI: return InternalFormat::RedGreenBlue16UnsignedInt;
        case GL_RGB32I: return InternalFormat::RedGreenBlue32Int;
        case GL_RGB32UI: return InternalFormat::RedGreenBlue32UnsignedInt;
        case GL_RGBA8I: return InternalFormat::RedGreenBlueAlpha8Int;
        case GL_RGBA8UI: return InternalFormat::RedGreenBlueAlpha8UnsignedInt;
        case GL_RGBA16I: return InternalFormat::RedGreenBlueAlpha16Int;
        case GL_RGBA16UI: return InternalFormat::RedGreenBlueAlpha16UnsignedInt;
        case GL_RGBA32I: return InternalFormat::RedGreenBlueAlpha32Int;
        case GL_RGBA32UI: return InternalFormat::RedGreenBlueAlpha32UnsignedInt;

        default: THROW(ArgumentOutOfRangeException{"Invalid internal format", "value"});
    }
}

template <>
Graphics::Format Graphics::FromOpenGl<Graphics::Format>(const int32_t value)
{
    switch (value)
    {
        case GL_RED: return Format::Red;
        case GL_RG: return Format::RedGreen;
        case GL_RGB: return Format::RedGreenBlue;
        case GL_BGR: return Format::BlueGreenRed;
        case GL_RGBA: return Format::RedGreenBlueAlpha;
        case GL_BGRA: return Format::BlueGreenRedAlpha;
        case GL_DEPTH_COMPONENT: return Format::DepthComponent;

        default: THROW(ArgumentOutOfRangeException{"Invalid format", "value"});
    }
}

template <>
Graphics::DataType Graphics::FromOpenGl<Graphics::DataType>(const int32_t value)
{
    switch (value)
    {
        case GL_UNSIGNED_BYTE: return DataType::UnsignedByte;
        case GL_BYTE: return DataType::Byte;
        case GL_UNSIGNED_SHORT: return DataType::UnsignedShort;
        case GL_SHORT: return DataType::Short;
        case GL_UNSIGNED_INT: return DataType::UnsignedInt;
        case GL_INT: return DataType::Int;
        case GL_FLOAT: return DataType::Float;

        case GL_UNSIGNED_BYTE_3_3_2: return DataType::UnsignedByte_3_3_2;
        case GL_UNSIGNED_BYTE_2_3_3_REV: return DataType::UnsignedByte_2_3_3_Reverse;

        case GL_UNSIGNED_SHORT_5_6_5: return DataType::UnsignedShort_5_6_5;
        case GL_UNSIGNED_SHORT_5_6_5_REV: return DataType::UnsignedShort_5_6_5_Reverse;
        case GL_UNSIGNED_SHORT_4_4_4_4: return DataType::UnsignedShort_4_4_4_4;
        case GL_UNSIGNED_SHORT_4_4_4_4_REV: return DataType::UnsignedShort_4_4_4_4_Reverse;
        case GL_UNSIGNED_SHORT_5_5_5_1: return DataType::UnsignedShort_5_5_5_1;
        case GL_UNSIGNED_SHORT_1_5_5_5_REV: return DataType::UnsignedShort_1_5_5_5_Reverse;

        case GL_UNSIGNED_INT_8_8_8_8: return DataType::UnsignedInt_8_8_8_8;
        case GL_UNSIGNED_INT_8_8_8_8_REV: return DataType::UnsignedInt_8_8_8_8_Reverse;
        case GL_UNSIGNED_INT_10_10_10_2: return DataType::UnsignedInt_10_10_10_2;
        case GL_UNSIGNED_INT_2_10_10_10_REV: return DataType::UnsignedInt_2_10_10_10_Reverse;

        default: THROW(ArgumentOutOfRangeException{"Invalid data type", "value"});
    }
}

template <>
Graphics::Constant Graphics::FromOpenGl<Graphics::Constant>(const int32_t value)
{
    switch (value)
    {
        case GL_ACTIVE_TEXTURE: return Constant::ActiveTexture;
        case GL_ALIASED_LINE_WIDTH_RANGE: return Constant::AliasedLineWidthRange;
        case GL_ARRAY_BUFFER_BINDING: return Constant::ArrayBufferBinding;
        case GL_BLEND: return Constant::Blend;
        case GL_BLEND_COLOR: return Constant::BlendColor;
        case GL_BLEND_DST_ALPHA: return Constant::BlendDstAlpha;
        case GL_BLEND_DST_RGB: return Constant::BlendDstRgb;
        case GL_BLEND_EQUATION_RGB: return Constant::BlendEquationRgb;
        case GL_BLEND_EQUATION_ALPHA: return Constant::BlendEquationAlpha;
        case GL_BLEND_SRC_ALPHA: return Constant::BlendSrcAlpha;
        case GL_BLEND_SRC_RGB: return Constant::BlendSrcRgb;
        case GL_COLOR_CLEAR_VALUE: return Constant::ColorClearValue;
        case GL_COLOR_LOGIC_OP: return Constant::ColorLogicOp;
        case GL_COLOR_WRITEMASK: return Constant::ColorWritemask;
        case GL_COMPRESSED_TEXTURE_FORMATS: return Constant::CompressedTextureFormats;
        case GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS: return Constant::MaxComputeShaderStorageBlocks;
        case GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS: return Constant::MaxCombinedShaderStorageBlocks;
        case GL_MAX_COMPUTE_UNIFORM_BLOCKS: return Constant::MaxComputeUniformBlocks;
        case GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS: return Constant::MaxComputeTextureImageUnits;
        case GL_MAX_COMPUTE_UNIFORM_COMPONENTS: return Constant::MaxComputeUniformComponents;
        case GL_MAX_COMPUTE_ATOMIC_COUNTERS: return Constant::MaxComputeAtomicCounters;
        case GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS: return Constant::MaxComputeAtomicCounterBuffers;
        case GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS: return Constant::MaxCombinedComputeUniformComponents;
        case GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS: return Constant::MaxComputeWorkGroupInvocations;
        case GL_MAX_COMPUTE_WORK_GROUP_COUNT: return Constant::MaxComputeWorkGroupCount;
        case GL_MAX_COMPUTE_WORK_GROUP_SIZE: return Constant::MaxComputeWorkGroupSize;
        case GL_DISPATCH_INDIRECT_BUFFER_BINDING: return Constant::DispatchIndirectBufferBinding;
        case GL_MAX_DEBUG_GROUP_STACK_DEPTH: return Constant::MaxDebugGroupStackDepth;
        case GL_DEBUG_GROUP_STACK_DEPTH: return Constant::DebugGroupStackDepth;
        case GL_CONTEXT_FLAGS: return Constant::ContextFlags;
        case GL_CULL_FACE: return Constant::CullFace;
        case GL_CULL_FACE_MODE: return Constant::CullFaceMode;
        case GL_CURRENT_PROGRAM: return Constant::CurrentProgram;
        case GL_DEPTH_CLEAR_VALUE: return Constant::DepthClearValue;
        case GL_DEPTH_FUNC: return Constant::DepthFunc;
        case GL_DEPTH_RANGE: return Constant::DepthRange;
        case GL_DEPTH_TEST: return Constant::DepthTest;
        case GL_DEPTH_WRITEMASK: return Constant::DepthWritemask;
        case GL_DITHER: return Constant::Dither;
        case GL_DOUBLEBUFFER: return Constant::DoubleBuffer;
        case GL_DRAW_BUFFER: return Constant::DrawBuffer;
        case GL_DRAW_BUFFER0: return Constant::DrawBuffer0;
        case GL_DRAW_BUFFER1: return Constant::DrawBuffer1;
        case GL_DRAW_BUFFER2: return Constant::DrawBuffer2;
        case GL_DRAW_BUFFER3: return Constant::DrawBuffer3;
        case GL_DRAW_BUFFER4: return Constant::DrawBuffer4;
        case GL_DRAW_BUFFER5: return Constant::DrawBuffer5;
        case GL_DRAW_BUFFER6: return Constant::DrawBuffer6;
        case GL_DRAW_BUFFER7: return Constant::DrawBuffer7;
        case GL_DRAW_BUFFER8: return Constant::DrawBuffer8;
        case GL_DRAW_BUFFER9: return Constant::DrawBuffer9;
        case GL_DRAW_BUFFER10: return Constant::DrawBuffer10;
        case GL_DRAW_BUFFER11: return Constant::DrawBuffer11;
        case GL_DRAW_BUFFER12: return Constant::DrawBuffer12;
        case GL_DRAW_BUFFER13: return Constant::DrawBuffer13;
        case GL_DRAW_BUFFER14: return Constant::DrawBuffer14;
        case GL_DRAW_BUFFER15: return Constant::DrawBuffer15;
        case GL_DRAW_FRAMEBUFFER_BINDING: return Constant::DrawFramebufferBinding;
        case GL_READ_FRAMEBUFFER_BINDING: return Constant::ReadFramebufferBinding;
        case GL_ELEMENT_ARRAY_BUFFER_BINDING: return Constant::ElementArrayBufferBinding;
        case GL_FRAGMENT_SHADER_DERIVATIVE_HINT: return Constant::FragmentShaderDerivativeHint;
        case GL_IMPLEMENTATION_COLOR_READ_FORMAT: return Constant::ImplementationColorReadFormat;
        case GL_IMPLEMENTATION_COLOR_READ_TYPE: return Constant::ImplementationColorReadType;
        case GL_LINE_SMOOTH: return Constant::LineSmooth;
        case GL_LINE_SMOOTH_HINT: return Constant::LineSmoothHint;
        case GL_LINE_WIDTH: return Constant::LineWidth;
        case GL_LAYER_PROVOKING_VERTEX: return Constant::LayerProvokingVertex;
        case GL_LOGIC_OP_MODE: return Constant::LogicOpMode;
        case GL_MAJOR_VERSION: return Constant::MajorVersion;
        case GL_MAX_3D_TEXTURE_SIZE: return Constant::Max3dTextureSize;
        case GL_MAX_ARRAY_TEXTURE_LAYERS: return Constant::MaxArrayTextureLayers;
        case GL_MAX_CLIP_DISTANCES: return Constant::MaxClipDistances;
        case GL_MAX_COLOR_TEXTURE_SAMPLES: return Constant::MaxColorTextureSamples;
        case GL_MAX_COMBINED_ATOMIC_COUNTERS: return Constant::MaxCombinedAtomicCounters;
        case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS: return Constant::MaxCombinedFragmentUniformComponents;
        case GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS: return Constant::MaxCombinedGeometryUniformComponents;
        case GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: return Constant::MaxCombinedTextureImageUnits;
        case GL_MAX_COMBINED_UNIFORM_BLOCKS: return Constant::MaxCombinedUniformBlocks;
        case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS: return Constant::MaxCombinedVertexUniformComponents;
        case GL_MAX_CUBE_MAP_TEXTURE_SIZE: return Constant::MaxCubeMapTextureSize;
        case GL_MAX_DEPTH_TEXTURE_SAMPLES: return Constant::MaxDepthTextureSamples;
        case GL_MAX_DRAW_BUFFERS: return Constant::MaxDrawBuffers;
        case GL_MAX_DUAL_SOURCE_DRAW_BUFFERS: return Constant::MaxDualSourceDrawBuffers;
        case GL_MAX_ELEMENTS_INDICES: return Constant::MaxElementsIndices;
        case GL_MAX_ELEMENTS_VERTICES: return Constant::MaxElementsVertices;
        case GL_MAX_FRAGMENT_ATOMIC_COUNTERS: return Constant::MaxFragmentAtomicCounters;
        case GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS: return Constant::MaxFragmentShaderStorageBlocks;
        case GL_MAX_FRAGMENT_INPUT_COMPONENTS: return Constant::MaxFragmentInputComponents;
        case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: return Constant::MaxFragmentUniformComponents;
        case GL_MAX_FRAGMENT_UNIFORM_VECTORS: return Constant::MaxFragmentUniformVectors;
        case GL_MAX_FRAGMENT_UNIFORM_BLOCKS: return Constant::MaxFragmentUniformBlocks;
        case GL_MAX_FRAMEBUFFER_WIDTH: return Constant::MaxFramebufferWidth;
        case GL_MAX_FRAMEBUFFER_HEIGHT: return Constant::MaxFramebufferHeight;
        case GL_MAX_FRAMEBUFFER_LAYERS: return Constant::MaxFramebufferLayers;
        case GL_MAX_FRAMEBUFFER_SAMPLES: return Constant::MaxFramebufferSamples;
        case GL_MAX_GEOMETRY_ATOMIC_COUNTERS: return Constant::MaxGeometryAtomicCounters;
        case GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS: return Constant::MaxGeometryShaderStorageBlocks;
        case GL_MAX_GEOMETRY_INPUT_COMPONENTS: return Constant::MaxGeometryInputComponents;
        case GL_MAX_GEOMETRY_OUTPUT_COMPONENTS: return Constant::MaxGeometryOutputComponents;
        case GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS: return Constant::MaxGeometryTextureImageUnits;
        case GL_MAX_GEOMETRY_UNIFORM_BLOCKS: return Constant::MaxGeometryUniformBlocks;
        case GL_MAX_GEOMETRY_UNIFORM_COMPONENTS: return Constant::MaxGeometryUniformComponents;
        case GL_MAX_INTEGER_SAMPLES: return Constant::MaxIntegerSamples;
        case GL_MIN_MAP_BUFFER_ALIGNMENT: return Constant::MinMapBufferAlignment;
        case GL_MAX_LABEL_LENGTH: return Constant::MaxLabelLength;
        case GL_MAX_PROGRAM_TEXEL_OFFSET: return Constant::MaxProgramTexelOffset;
        case GL_MIN_PROGRAM_TEXEL_OFFSET: return Constant::MinProgramTexelOffset;
        case GL_MAX_RECTANGLE_TEXTURE_SIZE: return Constant::MaxRectangleTextureSize;
        case GL_MAX_RENDERBUFFER_SIZE: return Constant::MaxRenderbufferSize;
        case GL_MAX_SAMPLE_MASK_WORDS: return Constant::MaxSampleMaskWords;
        case GL_MAX_SERVER_WAIT_TIMEOUT: return Constant::MaxServerWaitTimeout;
        case GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS: return Constant::MaxShaderStorageBufferBindings;
        case GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS: return Constant::MaxTessControlAtomicCounters;
        case GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS: return Constant::MaxTessEvaluationAtomicCounters;
        case GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS: return Constant::MaxTessControlShaderStorageBlocks;
        case GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS: return Constant::MaxTessEvaluationShaderStorageBlocks;
        case GL_MAX_TEXTURE_BUFFER_SIZE: return Constant::MaxTextureBufferSize;
        case GL_MAX_TEXTURE_IMAGE_UNITS: return Constant::MaxTextureImageUnits;
        case GL_MAX_TEXTURE_LOD_BIAS: return Constant::MaxTextureLodBias;
        case GL_MAX_TEXTURE_SIZE: return Constant::MaxTextureSize;
        case GL_MAX_UNIFORM_BUFFER_BINDINGS: return Constant::MaxUniformBufferBindings;
        case GL_MAX_UNIFORM_BLOCK_SIZE: return Constant::MaxUniformBlockSize;
        case GL_MAX_UNIFORM_LOCATIONS: return Constant::MaxUniformLocations;
        case GL_MAX_VARYING_COMPONENTS: return Constant::MaxVaryingComponents;
        case GL_MAX_VARYING_VECTORS: return Constant::MaxVaryingVectors;
        //case GL_MAX_VARYING_FLOATS: return Constant::MaxVaryingFloats; // FIXME - For some reason, GL_MAX_VARYING_COMPONENTS and GL_MAX_VARYING_FLOATS have the same value
        case GL_MAX_VERTEX_ATOMIC_COUNTERS: return Constant::MaxVertexAtomicCounters;
        case GL_MAX_VERTEX_ATTRIBS: return Constant::MaxVertexAttribs;
        case GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS: return Constant::MaxVertexShaderStorageBlocks;
        case GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: return Constant::MaxVertexTextureImageUnits;
        case GL_MAX_VERTEX_UNIFORM_COMPONENTS: return Constant::MaxVertexUniformComponents;
        case GL_MAX_VERTEX_UNIFORM_VECTORS: return Constant::MaxVertexUniformVectors;
        case GL_MAX_VERTEX_OUTPUT_COMPONENTS: return Constant::MaxVertexOutputComponents;
        case GL_MAX_VERTEX_UNIFORM_BLOCKS: return Constant::MaxVertexUniformBlocks;
        case GL_MAX_VIEWPORT_DIMS: return Constant::MaxViewportDims;
        case GL_MAX_VIEWPORTS: return Constant::MaxViewports;
        case GL_MINOR_VERSION: return Constant::MinorVersion;
        case GL_NUM_COMPRESSED_TEXTURE_FORMATS: return Constant::NumCompressedTextureFormats;
        case GL_NUM_EXTENSIONS: return Constant::NumExtensions;
        case GL_NUM_PROGRAM_BINARY_FORMATS: return Constant::NumProgramBinaryFormats;
        case GL_NUM_SHADER_BINARY_FORMATS: return Constant::NumShaderBinaryFormats;
        case GL_PACK_ALIGNMENT: return Constant::PackAlignment;
        case GL_PACK_IMAGE_HEIGHT: return Constant::PackImageHeight;
        case GL_PACK_LSB_FIRST: return Constant::PackLsbFirst;
        case GL_PACK_ROW_LENGTH: return Constant::PackRowLength;
        case GL_PACK_SKIP_IMAGES: return Constant::PackSkipImages;
        case GL_PACK_SKIP_PIXELS: return Constant::PackSkipPixels;
        case GL_PACK_SKIP_ROWS: return Constant::PackSkipRows;
        case GL_PACK_SWAP_BYTES: return Constant::PackSwapBytes;
        case GL_PIXEL_PACK_BUFFER_BINDING: return Constant::PixelPackBufferBinding;
        case GL_PIXEL_UNPACK_BUFFER_BINDING: return Constant::PixelUnpackBufferBinding;
        case GL_POINT_FADE_THRESHOLD_SIZE: return Constant::PointFadeThresholdSize;
        case GL_PRIMITIVE_RESTART_INDEX: return Constant::PrimitiveRestartIndex;
        case GL_PROGRAM_BINARY_FORMATS: return Constant::ProgramBinaryFormats;
        case GL_PROGRAM_PIPELINE_BINDING: return Constant::ProgramPipelineBinding;
        case GL_PROGRAM_POINT_SIZE: return Constant::ProgramPointSize;
        case GL_PROVOKING_VERTEX: return Constant::ProvokingVertex;
        case GL_POINT_SIZE: return Constant::PointSize;
        case GL_POINT_SIZE_GRANULARITY: return Constant::PointSizeGranularity;
        case GL_POINT_SIZE_RANGE: return Constant::PointSizeRange;
        case GL_POLYGON_OFFSET_FACTOR: return Constant::PolygonOffsetFactor;
        case GL_POLYGON_OFFSET_UNITS: return Constant::PolygonOffsetUnits;
        case GL_POLYGON_OFFSET_FILL: return Constant::PolygonOffsetFill;
        case GL_POLYGON_OFFSET_LINE: return Constant::PolygonOffsetLine;
        case GL_POLYGON_OFFSET_POINT: return Constant::PolygonOffsetPoint;
        case GL_POLYGON_SMOOTH: return Constant::PolygonSmooth;
        case GL_POLYGON_SMOOTH_HINT: return Constant::PolygonSmoothHint;
        case GL_READ_BUFFER: return Constant::ReadBuffer;
        case GL_RENDERBUFFER_BINDING: return Constant::RenderbufferBinding;
        case GL_SAMPLE_BUFFERS: return Constant::SampleBuffers;
        case GL_SAMPLE_COVERAGE_VALUE: return Constant::SampleCoverageValue;
        case GL_SAMPLE_COVERAGE_INVERT: return Constant::SampleCoverageInvert;
        case GL_SAMPLE_MASK_VALUE: return Constant::SampleMaskValue;
        case GL_SAMPLER_BINDING: return Constant::SamplerBinding;
        case GL_SAMPLES: return Constant::Samples;
        case GL_SCISSOR_BOX: return Constant::ScissorBox;
        case GL_SCISSOR_TEST: return Constant::ScissorTest;
        case GL_SHADER_COMPILER: return Constant::ShaderCompiler;
        case GL_SHADER_STORAGE_BUFFER_BINDING: return Constant::ShaderStorageBufferBinding;
        case GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT: return Constant::ShaderStorageBufferOffsetAlignment;
        case GL_SHADER_STORAGE_BUFFER_START: return Constant::ShaderStorageBufferStart;
        case GL_SHADER_STORAGE_BUFFER_SIZE: return Constant::ShaderStorageBufferSize;
        case GL_SMOOTH_LINE_WIDTH_RANGE: return Constant::SmoothLineWidthRange;
        case GL_SMOOTH_LINE_WIDTH_GRANULARITY: return Constant::SmoothLineWidthGranularity;
        case GL_STENCIL_BACK_FAIL: return Constant::StencilBackFail;
        case GL_STENCIL_BACK_FUNC: return Constant::StencilBackFunc;
        case GL_STENCIL_BACK_PASS_DEPTH_FAIL: return Constant::StencilBackPassDepthFail;
        case GL_STENCIL_BACK_PASS_DEPTH_PASS: return Constant::StencilBackPassDepthPass;
        case GL_STENCIL_BACK_REF: return Constant::StencilBackRef;
        case GL_STENCIL_BACK_VALUE_MASK: return Constant::StencilBackValueMask;
        case GL_STENCIL_BACK_WRITEMASK: return Constant::StencilBackWritemask;
        case GL_STENCIL_CLEAR_VALUE: return Constant::StencilClearValue;
        case GL_STENCIL_FAIL: return Constant::StencilFail;
        case GL_STENCIL_FUNC: return Constant::StencilFunc;
        case GL_STENCIL_PASS_DEPTH_FAIL: return Constant::StencilPassDepthFail;
        case GL_STENCIL_PASS_DEPTH_PASS: return Constant::StencilPassDepthPass;
        case GL_STENCIL_REF: return Constant::StencilRef;
        case GL_STENCIL_TEST: return Constant::StencilTest;
        case GL_STENCIL_VALUE_MASK: return Constant::StencilValueMask;
        case GL_STENCIL_WRITEMASK: return Constant::StencilWritemask;
        case GL_STEREO: return Constant::Stereo;
        case GL_SUBPIXEL_BITS: return Constant::SubpixelBits;
        case GL_TEXTURE_BINDING_1D: return Constant::TextureBinding1d;
        case GL_TEXTURE_BINDING_1D_ARRAY: return Constant::TextureBinding1dArray;
        case GL_TEXTURE_BINDING_2D: return Constant::TextureBinding2d;
        case GL_TEXTURE_BINDING_2D_ARRAY: return Constant::TextureBinding2dArray;
        case GL_TEXTURE_BINDING_2D_MULTISAMPLE: return Constant::TextureBinding2dMultisample;
        case GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY: return Constant::TextureBinding2dMultisampleArray;
        case GL_TEXTURE_BINDING_3D: return Constant::TextureBinding3d;
        case GL_TEXTURE_BINDING_BUFFER: return Constant::TextureBindingBuffer;
        case GL_TEXTURE_BINDING_CUBE_MAP: return Constant::TextureBindingCubeMap;
        case GL_TEXTURE_BINDING_RECTANGLE: return Constant::TextureBindingRectangle;
        case GL_TEXTURE_COMPRESSION_HINT: return Constant::TextureCompressionHint;
        case GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT: return Constant::TextureBufferOffsetAlignment;
        case GL_TIMESTAMP: return Constant::Timestamp;
        case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING: return Constant::TransformFeedbackBufferBinding;
        case GL_TRANSFORM_FEEDBACK_BUFFER_START: return Constant::TransformFeedbackBufferStart;
        case GL_TRANSFORM_FEEDBACK_BUFFER_SIZE: return Constant::TransformFeedbackBufferSize;
        case GL_UNIFORM_BUFFER_BINDING: return Constant::UniformBufferBinding;
        case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT: return Constant::UniformBufferOffsetAlignment;
        case GL_UNIFORM_BUFFER_SIZE: return Constant::UniformBufferSize;
        case GL_UNIFORM_BUFFER_START: return Constant::UniformBufferStart;
        case GL_UNPACK_ALIGNMENT: return Constant::UnpackAlignment;
        case GL_UNPACK_IMAGE_HEIGHT: return Constant::UnpackImageHeight;
        case GL_UNPACK_LSB_FIRST: return Constant::UnpackLsbFirst;
        case GL_UNPACK_ROW_LENGTH: return Constant::UnpackRowLength;
        case GL_UNPACK_SKIP_IMAGES: return Constant::UnpackSkipImages;
        case GL_UNPACK_SKIP_PIXELS: return Constant::UnpackSkipPixels;
        case GL_UNPACK_SKIP_ROWS: return Constant::UnpackSkipRows;
        case GL_UNPACK_SWAP_BYTES: return Constant::UnpackSwapBytes;
        case GL_VERTEX_ARRAY_BINDING: return Constant::VertexArrayBinding;
        case GL_VERTEX_BINDING_DIVISOR: return Constant::VertexBindingDivisor;
        case GL_VERTEX_BINDING_OFFSET: return Constant::VertexBindingOffset;
        case GL_VERTEX_BINDING_STRIDE: return Constant::VertexBindingStride;
        case GL_VERTEX_BINDING_BUFFER: return Constant::VertexBindingBuffer;
        case GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET: return Constant::MaxVertexAttribRelativeOffset;
        case GL_MAX_VERTEX_ATTRIB_BINDINGS: return Constant::MaxVertexAttribBindings;
        case GL_VIEWPORT: return Constant::Viewport;
        case GL_VIEWPORT_BOUNDS_RANGE: return Constant::ViewportBoundsRange;
        case GL_VIEWPORT_INDEX_PROVOKING_VERTEX: return Constant::ViewportIndexProvokingVertex;
        case GL_VIEWPORT_SUBPIXEL_BITS: return Constant::ViewportSubpixelBits;
        case GL_MAX_ELEMENT_INDEX: return Constant::MaxElementIndex;

        default: THROW(ArgumentOutOfRangeException{"Invalid constant", "value"});
    }
}

template <>
Graphics::BufferType Graphics::FromOpenGl<Graphics::BufferType>(const int32_t value)
{
    switch (value)
    {
        case GL_ARRAY_BUFFER: return BufferType::ArrayBuffer;
        case GL_ATOMIC_COUNTER_BUFFER: return BufferType::AtomicCounterBuffer;
        case GL_COPY_READ_BUFFER: return BufferType::CopyReadBuffer;
        case GL_COPY_WRITE_BUFFER: return BufferType::CopyWriteBuffer;
        case GL_DISPATCH_INDIRECT_BUFFER: return BufferType::DispatchIndirectBuffer;
        case GL_DRAW_INDIRECT_BUFFER: return BufferType::DrawIndirectBuffer;
        case GL_ELEMENT_ARRAY_BUFFER: return BufferType::ElementArrayBuffer;
        case GL_PIXEL_PACK_BUFFER: return BufferType::PixelPackBuffer;
        case GL_PIXEL_UNPACK_BUFFER: return BufferType::PixelUnpackBuffer;
        case GL_QUERY_BUFFER: return BufferType::QueryBuffer;
        case GL_SHADER_STORAGE_BUFFER: return BufferType::ShaderStorageBuffer;
        case GL_TEXTURE_BUFFER: return BufferType::TextureBuffer;
        case GL_TRANSFORM_FEEDBACK_BUFFER: return BufferType::TransformFeedbackBuffer;
        case GL_UNIFORM_BUFFER: return BufferType::UniformBuffer;

        default: THROW(ArgumentOutOfRangeException{"Invalid buffer type", "value"});
    }
}

template <>
Graphics::BufferUsage Graphics::FromOpenGl<Graphics::BufferUsage>(const int32_t value)
{
    switch (value)
    {
        case GL_STREAM_DRAW: return BufferUsage::StreamDraw;
        case GL_STREAM_READ: return BufferUsage::StreamRead;
        case GL_STREAM_COPY: return BufferUsage::StreamCopy;
        case GL_STATIC_DRAW: return BufferUsage::StaticDraw;
        case GL_STATIC_READ: return BufferUsage::StaticRead;
        case GL_STATIC_COPY: return BufferUsage::StaticCopy;
        case GL_DYNAMIC_DRAW: return BufferUsage::DynamicDraw;
        case GL_DYNAMIC_READ: return BufferUsage::DynamicRead;
        case GL_DYNAMIC_COPY: return BufferUsage::DynamicCopy;

        default: THROW(ArgumentOutOfRangeException{"Invalid buffer usage", "value"});
    }
}

template <>
Graphics::DrawMode Graphics::FromOpenGl<Graphics::DrawMode>(const int32_t value)
{
    switch (value)
    {
        case GL_POINTS: return DrawMode::Points;
        case GL_LINE_STRIP: return DrawMode::LineStrip;
        case GL_LINE_LOOP: return DrawMode::LineLoop;
        case GL_LINES: return DrawMode::Lines;
        case GL_LINE_STRIP_ADJACENCY: return DrawMode::LineStripAdjacency;
        case GL_LINES_ADJACENCY: return DrawMode::LinesAdjacency;
        case GL_TRIANGLE_STRIP: return DrawMode::TriangleStrip;
        case GL_TRIANGLE_FAN: return DrawMode::TriangleFan;
        case GL_TRIANGLES: return DrawMode::Triangles;
        case GL_TRIANGLE_STRIP_ADJACENCY: return DrawMode::TriangleStripAdjacency;
        case GL_TRIANGLES_ADJACENCY: return DrawMode::TrianglesAdjacency;
        case GL_PATCHES: return DrawMode::Patches;

        default: THROW(ArgumentOutOfRangeException{"Invalid draw mode", "value"});
    }
}

template <>
Graphics::BlendFunction Graphics::FromOpenGl<Graphics::BlendFunction>(const int32_t value)
{
    switch (value)
    {
        case GL_ZERO: return BlendFunction::Zero;
        case GL_ONE: return BlendFunction::One;
        case GL_SRC_COLOR: return BlendFunction::SrcColor;
        case GL_ONE_MINUS_SRC_COLOR: return BlendFunction::OneMinusSrcColor;
        case GL_DST_COLOR: return BlendFunction::DstColor;
        case GL_ONE_MINUS_DST_COLOR: return BlendFunction::OneMinusDstColor;
        case GL_SRC_ALPHA: return BlendFunction::SrcAlpha;
        case GL_ONE_MINUS_SRC_ALPHA: return BlendFunction::OneMinusSrcAlpha;
        case GL_DST_ALPHA: return BlendFunction::DstAlpha;
        case GL_ONE_MINUS_DST_ALPHA: return BlendFunction::OneMinusDstAlpha;
        case GL_CONSTANT_COLOR: return BlendFunction::ConstantColor;
        case GL_ONE_MINUS_CONSTANT_COLOR: return BlendFunction::OneMinusConstantColor;
        case GL_CONSTANT_ALPHA: return BlendFunction::ConstantAlpha;
        case GL_ONE_MINUS_CONSTANT_ALPHA: return BlendFunction::OneMinusConstantAlpha;

        default: THROW(ArgumentOutOfRangeException{"Invalid blend function", "value"});
    }
}

template <>
Graphics::FramebufferType Graphics::FromOpenGl<Graphics::FramebufferType>(const int32_t value)
{
    switch (value)
    {
        case GL_DRAW_FRAMEBUFFER: return FramebufferType::DrawFramebuffer;
        case GL_READ_FRAMEBUFFER: return FramebufferType::ReadFramebuffer;
        case GL_FRAMEBUFFER: return FramebufferType::Framebuffer;

        default: THROW(ArgumentOutOfRangeException{"Invalid blend function", "value"});
    }
}

template <>
Graphics::FramebufferStatus Graphics::FromOpenGl<Graphics::FramebufferStatus>(const int32_t value)
{
    switch (value)
    {
        case GL_FRAMEBUFFER_COMPLETE: return FramebufferStatus::Complete;
        case GL_FRAMEBUFFER_UNDEFINED: return FramebufferStatus::Undefined;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: return FramebufferStatus::IncompleteAttachment;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: return FramebufferStatus::IncompleteMissingAttachment;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: return FramebufferStatus::IncompleteDrawBuffer;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: return FramebufferStatus::IncompleteReadBuffer;
        case GL_FRAMEBUFFER_UNSUPPORTED: return FramebufferStatus::Unsupported;
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: return FramebufferStatus::IncompleteMultisample;
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: return FramebufferStatus::IncompleteLayerTargets;

        default: THROW(ArgumentOutOfRangeException{"Invalid framebuffer status", "value"});
    }
}

template <>
Graphics::FramebufferAttachment Graphics::FromOpenGl<Graphics::FramebufferAttachment>(const int32_t value)
{
    switch (value)
    {
        case GL_COLOR_ATTACHMENT0: return FramebufferAttachment::Color0;
        case GL_COLOR_ATTACHMENT1: return FramebufferAttachment::Color1;
        case GL_COLOR_ATTACHMENT2: return FramebufferAttachment::Color2;
        case GL_COLOR_ATTACHMENT3: return FramebufferAttachment::Color3;
        case GL_COLOR_ATTACHMENT4: return FramebufferAttachment::Color4;
        case GL_COLOR_ATTACHMENT5: return FramebufferAttachment::Color5;
        case GL_COLOR_ATTACHMENT6: return FramebufferAttachment::Color6;
        case GL_COLOR_ATTACHMENT7: return FramebufferAttachment::Color7;
        case GL_COLOR_ATTACHMENT8: return FramebufferAttachment::Color8;
        case GL_COLOR_ATTACHMENT9: return FramebufferAttachment::Color9;
        case GL_COLOR_ATTACHMENT10: return FramebufferAttachment::Color10;
        case GL_COLOR_ATTACHMENT11: return FramebufferAttachment::Color11;
        case GL_COLOR_ATTACHMENT12: return FramebufferAttachment::Color12;
        case GL_COLOR_ATTACHMENT13: return FramebufferAttachment::Color13;
        case GL_COLOR_ATTACHMENT14: return FramebufferAttachment::Color14;
        case GL_COLOR_ATTACHMENT15: return FramebufferAttachment::Color15;
        case GL_COLOR_ATTACHMENT16: return FramebufferAttachment::Color16;
        case GL_COLOR_ATTACHMENT17: return FramebufferAttachment::Color17;
        case GL_COLOR_ATTACHMENT18: return FramebufferAttachment::Color18;
        case GL_COLOR_ATTACHMENT19: return FramebufferAttachment::Color19;
        case GL_COLOR_ATTACHMENT20: return FramebufferAttachment::Color20;
        case GL_COLOR_ATTACHMENT21: return FramebufferAttachment::Color21;
        case GL_COLOR_ATTACHMENT22: return FramebufferAttachment::Color22;
        case GL_COLOR_ATTACHMENT23: return FramebufferAttachment::Color23;
        case GL_COLOR_ATTACHMENT24: return FramebufferAttachment::Color24;
        case GL_COLOR_ATTACHMENT25: return FramebufferAttachment::Color25;
        case GL_COLOR_ATTACHMENT26: return FramebufferAttachment::Color26;
        case GL_COLOR_ATTACHMENT27: return FramebufferAttachment::Color27;
        case GL_COLOR_ATTACHMENT28: return FramebufferAttachment::Color28;
        case GL_COLOR_ATTACHMENT29: return FramebufferAttachment::Color29;
        case GL_COLOR_ATTACHMENT30: return FramebufferAttachment::Color30;
        case GL_COLOR_ATTACHMENT31: return FramebufferAttachment::Color31;
        case GL_DEPTH_ATTACHMENT: return FramebufferAttachment::Depth;
        case GL_STENCIL_ATTACHMENT: return FramebufferAttachment::Stencil;
        case GL_DEPTH_STENCIL_ATTACHMENT: return FramebufferAttachment::DepthStencil;

        default: THROW(ArgumentOutOfRangeException{"Invalid framebuffer attachment", "value"});
    }
}

int32_t Graphics::ToOpenGl(const MagnificationFilter value)
{
    switch (value)
    {
        case MagnificationFilter::Nearest: return GL_NEAREST;
        case MagnificationFilter::Linear: return GL_LINEAR;
    }

    THROW(ArgumentOutOfRangeException{"Invalid magnification filter", "value"});
}

int32_t Graphics::ToOpenGl(const Wrapping value)
{
    switch (value)
    {
        case Wrapping::Repeat: return GL_REPEAT;
        case Wrapping::MirroredRepeat: return GL_MIRRORED_REPEAT;
        case Wrapping::ClampToEdge: return GL_CLAMP_TO_EDGE;
        case Wrapping::ClampToBorder: return GL_CLAMP_TO_BORDER;
    }

    THROW(ArgumentOutOfRangeException{"Invalid wrapping", "value"});
}

int32_t Graphics::ToOpenGl(const ShaderType value)
{
    switch (value)
    {
        case ShaderType::Vertex: return GL_VERTEX_SHADER;
        case ShaderType::Fragment: return GL_FRAGMENT_SHADER;
        case ShaderType::Geometry: return GL_GEOMETRY_SHADER;
    }

    THROW(ArgumentOutOfRangeException{"Invalid shader type", "value"});
}

int32_t Graphics::ToOpenGl(const InternalFormat value)
{
    switch (value)
    {
        case InternalFormat::DepthComponent: return GL_DEPTH_COMPONENT;
        case InternalFormat::DepthStencil: return GL_DEPTH_STENCIL;
        case InternalFormat::Red: return GL_RED;
        case InternalFormat::RedGreen: return GL_RG;
        case InternalFormat::RedGreenBlue: return GL_RGB;
        case InternalFormat::RedGreenBlueAlpha: return GL_RGBA;

        case InternalFormat::DepthComponent16: return GL_DEPTH_COMPONENT16;
        case InternalFormat::DepthComponent24: return GL_DEPTH_COMPONENT24;
        case InternalFormat::DepthComponent32Float: return GL_DEPTH_COMPONENT32F;
        case InternalFormat::Red8: return GL_R8;
        case InternalFormat::Red8Signed: return GL_R8_SNORM;
        case InternalFormat::Red16: return GL_R16;
        case InternalFormat::Red16Signed: return GL_R16_SNORM;
        case InternalFormat::RedGreen8: return GL_RG8;
        case InternalFormat::RedGreen8Signed: return GL_RG8_SNORM;
        case InternalFormat::RedGreen16: return GL_RG16;
        case InternalFormat::RedGreen16Signed: return GL_RG16_SNORM;
        case InternalFormat::Red3Green3Blue2: return GL_R3_G3_B2;
        case InternalFormat::RedGreenBlue4: return GL_RGB4;
        case InternalFormat::RedGreenBlue5: return GL_RGB5;
        case InternalFormat::RedGreenBlue8: return GL_RGB8;
        case InternalFormat::RedGreenBlue8Signed: return GL_RGB8_SNORM;
        case InternalFormat::RedGreenBlue10: return GL_RGB10;
        case InternalFormat::RedGreenBlue12: return GL_RGB12;
        case InternalFormat::RedGreenBlue16: return GL_RGB16;
        case InternalFormat::RedGreenBlue16Signed: return GL_RGB16_SNORM;
        case InternalFormat::RedGreenBlueAlpha2: return GL_RGBA2;
        case InternalFormat::RedGreenBlueAlpha4: return GL_RGBA4;
        case InternalFormat::RedGreenBlue5Alpha1: return GL_RGB5_A1;
        case InternalFormat::RedGreenBlueAlpha8: return GL_RGBA8;
        case InternalFormat::RedGreenBlueAlpha8Signed: return GL_RGBA8_SNORM;
        case InternalFormat::RedGreenBlue10Alpha2: return GL_RGB10_A2;
        case InternalFormat::RedGreenBlue10Alpha2UnsignedInt: return GL_RGB10_A2UI;
        case InternalFormat::RedGreenBlueAlpha12: return GL_RGBA12;
        case InternalFormat::RedGreenBlueAlpha16: return GL_RGBA16;
        case InternalFormat::SignedRedGreenBlue8: return GL_SRGB8;
        case InternalFormat::SignedRedGreenBlueAlpha8: return GL_SRGB8_ALPHA8;
        case InternalFormat::Red16Float: return GL_R16F;
        case InternalFormat::RedGreen16Float: return GL_RG16F;
        case InternalFormat::RedGreenBlue16Float: return GL_RGB16F;
        case InternalFormat::RedGreenBlueAlpha16Float: return GL_RGBA16F;
        case InternalFormat::Red32Float: return GL_R32F;
        case InternalFormat::RedGreen32Float: return GL_RG32F;
        case InternalFormat::RedGreenBlue32Float: return GL_RGB32F;
        case InternalFormat::RedGreenBlueAlpha32Float: return GL_RGBA32F;
        case InternalFormat::Red11FloatGreen11FloatBlue10Float: return GL_R11F_G11F_B10F;
        case InternalFormat::RedGreenBlue9Shared5: return GL_RGB9_E5;
        case InternalFormat::Red8Int: return GL_R8I;
        case InternalFormat::Red8UnsignedInt: return GL_R8UI;
        case InternalFormat::Red16Int: return GL_R16I;
        case InternalFormat::Red16UnsignedInt: return GL_R16UI;
        case InternalFormat::Red32Int: return GL_R32I;
        case InternalFormat::Red32UnsignedInt: return GL_R32UI;
        case InternalFormat::RedGreen8Int: return GL_RG8I;
        case InternalFormat::RedGreen8UnsignedInt: return GL_RG8UI;
        case InternalFormat::RedGreen16Int: return GL_RG16I;
        case InternalFormat::RedGreen16UnsignedInt: return GL_RG16UI;
        case InternalFormat::RedGreen32Int: return GL_RG32I;
        case InternalFormat::RedGreen32UnsignedInt: return GL_RG32UI;
        case InternalFormat::RedGreenBlue8Int: return GL_RGB8I;
        case InternalFormat::RedGreenBlue8UnsignedInt: return GL_RGB8UI;
        case InternalFormat::RedGreenBlue16Int: return GL_RGB16I;
        case InternalFormat::RedGreenBlue16UnsignedInt: return GL_RGB16UI;
        case InternalFormat::RedGreenBlue32Int: return GL_RGB32I;
        case InternalFormat::RedGreenBlue32UnsignedInt: return GL_RGB32UI;
        case InternalFormat::RedGreenBlueAlpha8Int: return GL_RGBA8I;
        case InternalFormat::RedGreenBlueAlpha8UnsignedInt: return GL_RGBA8UI;
        case InternalFormat::RedGreenBlueAlpha16Int: return GL_RGBA16I;
        case InternalFormat::RedGreenBlueAlpha16UnsignedInt: return GL_RGBA16UI;
        case InternalFormat::RedGreenBlueAlpha32Int: return GL_RGBA32I;
        case InternalFormat::RedGreenBlueAlpha32UnsignedInt: return GL_RGBA32UI;
    }

    THROW(ArgumentOutOfRangeException{"Invalid internal format", "value"});
}

int32_t Graphics::ToOpenGl(const Format value)
{
    switch (value)
    {
        case Format::Red: return GL_RED;
        case Format::RedGreen: return GL_RG;
        case Format::RedGreenBlue: return GL_RGB;
        case Format::BlueGreenRed: return GL_BGR;
        case Format::RedGreenBlueAlpha: return GL_RGBA;
        case Format::BlueGreenRedAlpha: return GL_BGRA;
        case Format::DepthComponent: return GL_DEPTH_COMPONENT;
    }

    THROW(ArgumentOutOfRangeException{"Invalid format", "value"});
}

int32_t Graphics::ToOpenGl(const DataType value)
{
    switch (value)
    {
        case DataType::UnsignedByte: return GL_UNSIGNED_BYTE;
        case DataType::Byte: return GL_BYTE;
        case DataType::UnsignedShort: return GL_UNSIGNED_SHORT;
        case DataType::Short: return GL_SHORT;
        case DataType::UnsignedInt: return GL_UNSIGNED_INT;
        case DataType::Int: return GL_INT;
        case DataType::Float: return GL_FLOAT;

        case DataType::UnsignedByte_3_3_2: return GL_UNSIGNED_BYTE_3_3_2;
        case DataType::UnsignedByte_2_3_3_Reverse: return GL_UNSIGNED_BYTE_2_3_3_REV;

        case DataType::UnsignedShort_5_6_5: return GL_UNSIGNED_SHORT_5_6_5;
        case DataType::UnsignedShort_5_6_5_Reverse: return GL_UNSIGNED_SHORT_5_6_5_REV;
        case DataType::UnsignedShort_4_4_4_4: return GL_UNSIGNED_SHORT_4_4_4_4;
        case DataType::UnsignedShort_4_4_4_4_Reverse: return GL_UNSIGNED_SHORT_4_4_4_4_REV;
        case DataType::UnsignedShort_5_5_5_1: return GL_UNSIGNED_SHORT_5_5_5_1;
        case DataType::UnsignedShort_1_5_5_5_Reverse: return GL_UNSIGNED_SHORT_1_5_5_5_REV;

        case DataType::UnsignedInt_8_8_8_8: return GL_UNSIGNED_INT_8_8_8_8;
        case DataType::UnsignedInt_8_8_8_8_Reverse: return GL_UNSIGNED_INT_8_8_8_8_REV;
        case DataType::UnsignedInt_10_10_10_2: return GL_UNSIGNED_INT_10_10_10_2;
        case DataType::UnsignedInt_2_10_10_10_Reverse: return GL_UNSIGNED_INT_2_10_10_10_REV;
    }

    THROW(ArgumentOutOfRangeException{"Invalid data type", "value"});
}

int32_t Graphics::ToOpenGl(const Constant value)
{
    switch (value)
    {
        case Constant::ActiveTexture: return GL_ACTIVE_TEXTURE;
        case Constant::AliasedLineWidthRange: return GL_ALIASED_LINE_WIDTH_RANGE;
        case Constant::ArrayBufferBinding: return GL_ARRAY_BUFFER_BINDING;
        case Constant::Blend: return GL_BLEND;
        case Constant::BlendColor: return GL_BLEND_COLOR;
        case Constant::BlendDstAlpha: return GL_BLEND_DST_ALPHA;
        case Constant::BlendDstRgb: return GL_BLEND_DST_RGB;
        case Constant::BlendEquationRgb: return GL_BLEND_EQUATION_RGB;
        case Constant::BlendEquationAlpha: return GL_BLEND_EQUATION_ALPHA;
        case Constant::BlendSrcAlpha: return GL_BLEND_SRC_ALPHA;
        case Constant::BlendSrcRgb: return GL_BLEND_SRC_RGB;
        case Constant::ColorClearValue: return GL_COLOR_CLEAR_VALUE;
        case Constant::ColorLogicOp: return GL_COLOR_LOGIC_OP;
        case Constant::ColorWritemask: return GL_COLOR_WRITEMASK;
        case Constant::CompressedTextureFormats: return GL_COMPRESSED_TEXTURE_FORMATS;
        case Constant::MaxComputeShaderStorageBlocks: return GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS;
        case Constant::MaxCombinedShaderStorageBlocks: return GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS;
        case Constant::MaxComputeUniformBlocks: return GL_MAX_COMPUTE_UNIFORM_BLOCKS;
        case Constant::MaxComputeTextureImageUnits: return GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS;
        case Constant::MaxComputeUniformComponents: return GL_MAX_COMPUTE_UNIFORM_COMPONENTS;
        case Constant::MaxComputeAtomicCounters: return GL_MAX_COMPUTE_ATOMIC_COUNTERS;
        case Constant::MaxComputeAtomicCounterBuffers: return GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS;
        case Constant::MaxCombinedComputeUniformComponents: return GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS;
        case Constant::MaxComputeWorkGroupInvocations: return GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS;
        case Constant::MaxComputeWorkGroupCount: return GL_MAX_COMPUTE_WORK_GROUP_COUNT;
        case Constant::MaxComputeWorkGroupSize: return GL_MAX_COMPUTE_WORK_GROUP_SIZE;
        case Constant::DispatchIndirectBufferBinding: return GL_DISPATCH_INDIRECT_BUFFER_BINDING;
        case Constant::MaxDebugGroupStackDepth: return GL_MAX_DEBUG_GROUP_STACK_DEPTH;
        case Constant::DebugGroupStackDepth: return GL_DEBUG_GROUP_STACK_DEPTH;
        case Constant::ContextFlags: return GL_CONTEXT_FLAGS;
        case Constant::CullFace: return GL_CULL_FACE;
        case Constant::CullFaceMode: return GL_CULL_FACE_MODE;
        case Constant::CurrentProgram: return GL_CURRENT_PROGRAM;
        case Constant::DepthClearValue: return GL_DEPTH_CLEAR_VALUE;
        case Constant::DepthFunc: return GL_DEPTH_FUNC;
        case Constant::DepthRange: return GL_DEPTH_RANGE;
        case Constant::DepthTest: return GL_DEPTH_TEST;
        case Constant::DepthWritemask: return GL_DEPTH_WRITEMASK;
        case Constant::Dither: return GL_DITHER;
        case Constant::DoubleBuffer: return GL_DOUBLEBUFFER;
        case Constant::DrawBuffer: return GL_DRAW_BUFFER;
        case Constant::DrawBuffer0: return GL_DRAW_BUFFER0;
        case Constant::DrawBuffer1: return GL_DRAW_BUFFER1;
        case Constant::DrawBuffer2: return GL_DRAW_BUFFER2;
        case Constant::DrawBuffer3: return GL_DRAW_BUFFER3;
        case Constant::DrawBuffer4: return GL_DRAW_BUFFER4;
        case Constant::DrawBuffer5: return GL_DRAW_BUFFER5;
        case Constant::DrawBuffer6: return GL_DRAW_BUFFER6;
        case Constant::DrawBuffer7: return GL_DRAW_BUFFER7;
        case Constant::DrawBuffer8: return GL_DRAW_BUFFER8;
        case Constant::DrawBuffer9: return GL_DRAW_BUFFER9;
        case Constant::DrawBuffer10: return GL_DRAW_BUFFER10;
        case Constant::DrawBuffer11: return GL_DRAW_BUFFER11;
        case Constant::DrawBuffer12: return GL_DRAW_BUFFER12;
        case Constant::DrawBuffer13: return GL_DRAW_BUFFER13;
        case Constant::DrawBuffer14: return GL_DRAW_BUFFER14;
        case Constant::DrawBuffer15: return GL_DRAW_BUFFER15;
        case Constant::DrawFramebufferBinding: return GL_DRAW_FRAMEBUFFER_BINDING;
        case Constant::ReadFramebufferBinding: return GL_READ_FRAMEBUFFER_BINDING;
        case Constant::ElementArrayBufferBinding: return GL_ELEMENT_ARRAY_BUFFER_BINDING;
        case Constant::FragmentShaderDerivativeHint: return GL_FRAGMENT_SHADER_DERIVATIVE_HINT;
        case Constant::ImplementationColorReadFormat: return GL_IMPLEMENTATION_COLOR_READ_FORMAT;
        case Constant::ImplementationColorReadType: return GL_IMPLEMENTATION_COLOR_READ_TYPE;
        case Constant::LineSmooth: return GL_LINE_SMOOTH;
        case Constant::LineSmoothHint: return GL_LINE_SMOOTH_HINT;
        case Constant::LineWidth: return GL_LINE_WIDTH;
        case Constant::LayerProvokingVertex: return GL_LAYER_PROVOKING_VERTEX;
        case Constant::LogicOpMode: return GL_LOGIC_OP_MODE;
        case Constant::MajorVersion: return GL_MAJOR_VERSION;
        case Constant::Max3dTextureSize: return GL_MAX_3D_TEXTURE_SIZE;
        case Constant::MaxArrayTextureLayers: return GL_MAX_ARRAY_TEXTURE_LAYERS;
        case Constant::MaxClipDistances: return GL_MAX_CLIP_DISTANCES;
        case Constant::MaxColorTextureSamples: return GL_MAX_COLOR_TEXTURE_SAMPLES;
        case Constant::MaxCombinedAtomicCounters: return GL_MAX_COMBINED_ATOMIC_COUNTERS;
        case Constant::MaxCombinedFragmentUniformComponents: return GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS;
        case Constant::MaxCombinedGeometryUniformComponents: return GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS;
        case Constant::MaxCombinedTextureImageUnits: return GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
        case Constant::MaxCombinedUniformBlocks: return GL_MAX_COMBINED_UNIFORM_BLOCKS;
        case Constant::MaxCombinedVertexUniformComponents: return GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS;
        case Constant::MaxCubeMapTextureSize: return GL_MAX_CUBE_MAP_TEXTURE_SIZE;
        case Constant::MaxDepthTextureSamples: return GL_MAX_DEPTH_TEXTURE_SAMPLES;
        case Constant::MaxDrawBuffers: return GL_MAX_DRAW_BUFFERS;
        case Constant::MaxDualSourceDrawBuffers: return GL_MAX_DUAL_SOURCE_DRAW_BUFFERS;
        case Constant::MaxElementsIndices: return GL_MAX_ELEMENTS_INDICES;
        case Constant::MaxElementsVertices: return GL_MAX_ELEMENTS_VERTICES;
        case Constant::MaxFragmentAtomicCounters: return GL_MAX_FRAGMENT_ATOMIC_COUNTERS;
        case Constant::MaxFragmentShaderStorageBlocks: return GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS;
        case Constant::MaxFragmentInputComponents: return GL_MAX_FRAGMENT_INPUT_COMPONENTS;
        case Constant::MaxFragmentUniformComponents: return GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;
        case Constant::MaxFragmentUniformVectors: return GL_MAX_FRAGMENT_UNIFORM_VECTORS;
        case Constant::MaxFragmentUniformBlocks: return GL_MAX_FRAGMENT_UNIFORM_BLOCKS;
        case Constant::MaxFramebufferWidth: return GL_MAX_FRAMEBUFFER_WIDTH;
        case Constant::MaxFramebufferHeight: return GL_MAX_FRAMEBUFFER_HEIGHT;
        case Constant::MaxFramebufferLayers: return GL_MAX_FRAMEBUFFER_LAYERS;
        case Constant::MaxFramebufferSamples: return GL_MAX_FRAMEBUFFER_SAMPLES;
        case Constant::MaxGeometryAtomicCounters: return GL_MAX_GEOMETRY_ATOMIC_COUNTERS;
        case Constant::MaxGeometryShaderStorageBlocks: return GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS;
        case Constant::MaxGeometryInputComponents: return GL_MAX_GEOMETRY_INPUT_COMPONENTS;
        case Constant::MaxGeometryOutputComponents: return GL_MAX_GEOMETRY_OUTPUT_COMPONENTS;
        case Constant::MaxGeometryTextureImageUnits: return GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS;
        case Constant::MaxGeometryUniformBlocks: return GL_MAX_GEOMETRY_UNIFORM_BLOCKS;
        case Constant::MaxGeometryUniformComponents: return GL_MAX_GEOMETRY_UNIFORM_COMPONENTS;
        case Constant::MaxIntegerSamples: return GL_MAX_INTEGER_SAMPLES;
        case Constant::MinMapBufferAlignment: return GL_MIN_MAP_BUFFER_ALIGNMENT;
        case Constant::MaxLabelLength: return GL_MAX_LABEL_LENGTH;
        case Constant::MaxProgramTexelOffset: return GL_MAX_PROGRAM_TEXEL_OFFSET;
        case Constant::MinProgramTexelOffset: return GL_MIN_PROGRAM_TEXEL_OFFSET;
        case Constant::MaxRectangleTextureSize: return GL_MAX_RECTANGLE_TEXTURE_SIZE;
        case Constant::MaxRenderbufferSize: return GL_MAX_RENDERBUFFER_SIZE;
        case Constant::MaxSampleMaskWords: return GL_MAX_SAMPLE_MASK_WORDS;
        case Constant::MaxServerWaitTimeout: return GL_MAX_SERVER_WAIT_TIMEOUT;
        case Constant::MaxShaderStorageBufferBindings: return GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS;
        case Constant::MaxTessControlAtomicCounters: return GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS;
        case Constant::MaxTessEvaluationAtomicCounters: return GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS;
        case Constant::MaxTessControlShaderStorageBlocks: return GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS;
        case Constant::MaxTessEvaluationShaderStorageBlocks: return GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS;
        case Constant::MaxTextureBufferSize: return GL_MAX_TEXTURE_BUFFER_SIZE;
        case Constant::MaxTextureImageUnits: return GL_MAX_TEXTURE_IMAGE_UNITS;
        case Constant::MaxTextureLodBias: return GL_MAX_TEXTURE_LOD_BIAS;
        case Constant::MaxTextureSize: return GL_MAX_TEXTURE_SIZE;
        case Constant::MaxUniformBufferBindings: return GL_MAX_UNIFORM_BUFFER_BINDINGS;
        case Constant::MaxUniformBlockSize: return GL_MAX_UNIFORM_BLOCK_SIZE;
        case Constant::MaxUniformLocations: return GL_MAX_UNIFORM_LOCATIONS;
        case Constant::MaxVaryingComponents: return GL_MAX_VARYING_COMPONENTS;
        case Constant::MaxVaryingVectors: return GL_MAX_VARYING_VECTORS;
        case Constant::MaxVaryingFloats: return GL_MAX_VARYING_FLOATS;
        case Constant::MaxVertexAtomicCounters: return GL_MAX_VERTEX_ATOMIC_COUNTERS;
        case Constant::MaxVertexAttribs: return GL_MAX_VERTEX_ATTRIBS;
        case Constant::MaxVertexShaderStorageBlocks: return GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS;
        case Constant::MaxVertexTextureImageUnits: return GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
        case Constant::MaxVertexUniformComponents: return GL_MAX_VERTEX_UNIFORM_COMPONENTS;
        case Constant::MaxVertexUniformVectors: return GL_MAX_VERTEX_UNIFORM_VECTORS;
        case Constant::MaxVertexOutputComponents: return GL_MAX_VERTEX_OUTPUT_COMPONENTS;
        case Constant::MaxVertexUniformBlocks: return GL_MAX_VERTEX_UNIFORM_BLOCKS;
        case Constant::MaxViewportDims: return GL_MAX_VIEWPORT_DIMS;
        case Constant::MaxViewports: return GL_MAX_VIEWPORTS;
        case Constant::MinorVersion: return GL_MINOR_VERSION;
        case Constant::NumCompressedTextureFormats: return GL_NUM_COMPRESSED_TEXTURE_FORMATS;
        case Constant::NumExtensions: return GL_NUM_EXTENSIONS;
        case Constant::NumProgramBinaryFormats: return GL_NUM_PROGRAM_BINARY_FORMATS;
        case Constant::NumShaderBinaryFormats: return GL_NUM_SHADER_BINARY_FORMATS;
        case Constant::PackAlignment: return GL_PACK_ALIGNMENT;
        case Constant::PackImageHeight: return GL_PACK_IMAGE_HEIGHT;
        case Constant::PackLsbFirst: return GL_PACK_LSB_FIRST;
        case Constant::PackRowLength: return GL_PACK_ROW_LENGTH;
        case Constant::PackSkipImages: return GL_PACK_SKIP_IMAGES;
        case Constant::PackSkipPixels: return GL_PACK_SKIP_PIXELS;
        case Constant::PackSkipRows: return GL_PACK_SKIP_ROWS;
        case Constant::PackSwapBytes: return GL_PACK_SWAP_BYTES;
        case Constant::PixelPackBufferBinding: return GL_PIXEL_PACK_BUFFER_BINDING;
        case Constant::PixelUnpackBufferBinding: return GL_PIXEL_UNPACK_BUFFER_BINDING;
        case Constant::PointFadeThresholdSize: return GL_POINT_FADE_THRESHOLD_SIZE;
        case Constant::PrimitiveRestartIndex: return GL_PRIMITIVE_RESTART_INDEX;
        case Constant::ProgramBinaryFormats: return GL_PROGRAM_BINARY_FORMATS;
        case Constant::ProgramPipelineBinding: return GL_PROGRAM_PIPELINE_BINDING;
        case Constant::ProgramPointSize: return GL_PROGRAM_POINT_SIZE;
        case Constant::ProvokingVertex: return GL_PROVOKING_VERTEX;
        case Constant::PointSize: return GL_POINT_SIZE;
        case Constant::PointSizeGranularity: return GL_POINT_SIZE_GRANULARITY;
        case Constant::PointSizeRange: return GL_POINT_SIZE_RANGE;
        case Constant::PolygonOffsetFactor: return GL_POLYGON_OFFSET_FACTOR;
        case Constant::PolygonOffsetUnits: return GL_POLYGON_OFFSET_UNITS;
        case Constant::PolygonOffsetFill: return GL_POLYGON_OFFSET_FILL;
        case Constant::PolygonOffsetLine: return GL_POLYGON_OFFSET_LINE;
        case Constant::PolygonOffsetPoint: return GL_POLYGON_OFFSET_POINT;
        case Constant::PolygonSmooth: return GL_POLYGON_SMOOTH;
        case Constant::PolygonSmoothHint: return GL_POLYGON_SMOOTH_HINT;
        case Constant::ReadBuffer: return GL_READ_BUFFER;
        case Constant::RenderbufferBinding: return GL_RENDERBUFFER_BINDING;
        case Constant::SampleBuffers: return GL_SAMPLE_BUFFERS;
        case Constant::SampleCoverageValue: return GL_SAMPLE_COVERAGE_VALUE;
        case Constant::SampleCoverageInvert: return GL_SAMPLE_COVERAGE_INVERT;
        case Constant::SampleMaskValue: return GL_SAMPLE_MASK_VALUE;
        case Constant::SamplerBinding: return GL_SAMPLER_BINDING;
        case Constant::Samples: return GL_SAMPLES;
        case Constant::ScissorBox: return GL_SCISSOR_BOX;
        case Constant::ScissorTest: return GL_SCISSOR_TEST;
        case Constant::ShaderCompiler: return GL_SHADER_COMPILER;
        case Constant::ShaderStorageBufferBinding: return GL_SHADER_STORAGE_BUFFER_BINDING;
        case Constant::ShaderStorageBufferOffsetAlignment: return GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT;
        case Constant::ShaderStorageBufferStart: return GL_SHADER_STORAGE_BUFFER_START;
        case Constant::ShaderStorageBufferSize: return GL_SHADER_STORAGE_BUFFER_SIZE;
        case Constant::SmoothLineWidthRange: return GL_SMOOTH_LINE_WIDTH_RANGE;
        case Constant::SmoothLineWidthGranularity: return GL_SMOOTH_LINE_WIDTH_GRANULARITY;
        case Constant::StencilBackFail: return GL_STENCIL_BACK_FAIL;
        case Constant::StencilBackFunc: return GL_STENCIL_BACK_FUNC;
        case Constant::StencilBackPassDepthFail: return GL_STENCIL_BACK_PASS_DEPTH_FAIL;
        case Constant::StencilBackPassDepthPass: return GL_STENCIL_BACK_PASS_DEPTH_PASS;
        case Constant::StencilBackRef: return GL_STENCIL_BACK_REF;
        case Constant::StencilBackValueMask: return GL_STENCIL_BACK_VALUE_MASK;
        case Constant::StencilBackWritemask: return GL_STENCIL_BACK_WRITEMASK;
        case Constant::StencilClearValue: return GL_STENCIL_CLEAR_VALUE;
        case Constant::StencilFail: return GL_STENCIL_FAIL;
        case Constant::StencilFunc: return GL_STENCIL_FUNC;
        case Constant::StencilPassDepthFail: return GL_STENCIL_PASS_DEPTH_FAIL;
        case Constant::StencilPassDepthPass: return GL_STENCIL_PASS_DEPTH_PASS;
        case Constant::StencilRef: return GL_STENCIL_REF;
        case Constant::StencilTest: return GL_STENCIL_TEST;
        case Constant::StencilValueMask: return GL_STENCIL_VALUE_MASK;
        case Constant::StencilWritemask: return GL_STENCIL_WRITEMASK;
        case Constant::Stereo: return GL_STEREO;
        case Constant::SubpixelBits: return GL_SUBPIXEL_BITS;
        case Constant::TextureBinding1d: return GL_TEXTURE_BINDING_1D;
        case Constant::TextureBinding1dArray: return GL_TEXTURE_BINDING_1D_ARRAY;
        case Constant::TextureBinding2d: return GL_TEXTURE_BINDING_2D;
        case Constant::TextureBinding2dArray: return GL_TEXTURE_BINDING_2D_ARRAY;
        case Constant::TextureBinding2dMultisample: return GL_TEXTURE_BINDING_2D_MULTISAMPLE;
        case Constant::TextureBinding2dMultisampleArray: return GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY;
        case Constant::TextureBinding3d: return GL_TEXTURE_BINDING_3D;
        case Constant::TextureBindingBuffer: return GL_TEXTURE_BINDING_BUFFER;
        case Constant::TextureBindingCubeMap: return GL_TEXTURE_BINDING_CUBE_MAP;
        case Constant::TextureBindingRectangle: return GL_TEXTURE_BINDING_RECTANGLE;
        case Constant::TextureCompressionHint: return GL_TEXTURE_COMPRESSION_HINT;
        case Constant::TextureBufferOffsetAlignment: return GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT;
        case Constant::Timestamp: return GL_TIMESTAMP;
        case Constant::TransformFeedbackBufferBinding: return GL_TRANSFORM_FEEDBACK_BUFFER_BINDING;
        case Constant::TransformFeedbackBufferStart: return GL_TRANSFORM_FEEDBACK_BUFFER_START;
        case Constant::TransformFeedbackBufferSize: return GL_TRANSFORM_FEEDBACK_BUFFER_SIZE;
        case Constant::UniformBufferBinding: return GL_UNIFORM_BUFFER_BINDING;
        case Constant::UniformBufferOffsetAlignment: return GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT;
        case Constant::UniformBufferSize: return GL_UNIFORM_BUFFER_SIZE;
        case Constant::UniformBufferStart: return GL_UNIFORM_BUFFER_START;
        case Constant::UnpackAlignment: return GL_UNPACK_ALIGNMENT;
        case Constant::UnpackImageHeight: return GL_UNPACK_IMAGE_HEIGHT;
        case Constant::UnpackLsbFirst: return GL_UNPACK_LSB_FIRST;
        case Constant::UnpackRowLength: return GL_UNPACK_ROW_LENGTH;
        case Constant::UnpackSkipImages: return GL_UNPACK_SKIP_IMAGES;
        case Constant::UnpackSkipPixels: return GL_UNPACK_SKIP_PIXELS;
        case Constant::UnpackSkipRows: return GL_UNPACK_SKIP_ROWS;
        case Constant::UnpackSwapBytes: return GL_UNPACK_SWAP_BYTES;
        case Constant::VertexArrayBinding: return GL_VERTEX_ARRAY_BINDING;
        case Constant::VertexBindingDivisor: return GL_VERTEX_BINDING_DIVISOR;
        case Constant::VertexBindingOffset: return GL_VERTEX_BINDING_OFFSET;
        case Constant::VertexBindingStride: return GL_VERTEX_BINDING_STRIDE;
        case Constant::VertexBindingBuffer: return GL_VERTEX_BINDING_BUFFER;
        case Constant::MaxVertexAttribRelativeOffset: return GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET;
        case Constant::MaxVertexAttribBindings: return GL_MAX_VERTEX_ATTRIB_BINDINGS;
        case Constant::Viewport: return GL_VIEWPORT;
        case Constant::ViewportBoundsRange: return GL_VIEWPORT_BOUNDS_RANGE;
        case Constant::ViewportIndexProvokingVertex: return GL_VIEWPORT_INDEX_PROVOKING_VERTEX;
        case Constant::ViewportSubpixelBits: return GL_VIEWPORT_SUBPIXEL_BITS;
        case Constant::MaxElementIndex: return GL_MAX_ELEMENT_INDEX;
    }

    THROW(ArgumentOutOfRangeException{"Invalid constant", "value"});
}

int32_t Graphics::ToOpenGl(const BufferType value)
{
    switch (value)
    {
        case BufferType::ArrayBuffer: return GL_ARRAY_BUFFER;
        case BufferType::AtomicCounterBuffer: return GL_ATOMIC_COUNTER_BUFFER;
        case BufferType::CopyReadBuffer: return GL_COPY_READ_BUFFER;
        case BufferType::CopyWriteBuffer: return GL_COPY_WRITE_BUFFER;
        case BufferType::DispatchIndirectBuffer: return GL_DISPATCH_INDIRECT_BUFFER;
        case BufferType::DrawIndirectBuffer: return GL_DRAW_INDIRECT_BUFFER;
        case BufferType::ElementArrayBuffer: return GL_ELEMENT_ARRAY_BUFFER;
        case BufferType::PixelPackBuffer: return GL_PIXEL_PACK_BUFFER;
        case BufferType::PixelUnpackBuffer: return GL_PIXEL_UNPACK_BUFFER;
        case BufferType::QueryBuffer: return GL_QUERY_BUFFER;
        case BufferType::ShaderStorageBuffer: return GL_SHADER_STORAGE_BUFFER;
        case BufferType::TextureBuffer: return GL_TEXTURE_BUFFER;
        case BufferType::TransformFeedbackBuffer: return GL_TRANSFORM_FEEDBACK_BUFFER;
        case BufferType::UniformBuffer: return GL_UNIFORM_BUFFER;
    }

    THROW(ArgumentOutOfRangeException{"Invalid buffer type", "value"});
}

int32_t Graphics::ToOpenGl(const BufferUsage value)
{
    switch (value)
    {
        case BufferUsage::StreamDraw: return GL_STREAM_DRAW;
        case BufferUsage::StreamRead: return GL_STREAM_READ;
        case BufferUsage::StreamCopy: return GL_STREAM_COPY;
        case BufferUsage::StaticDraw: return GL_STATIC_DRAW;
        case BufferUsage::StaticRead: return GL_STATIC_READ;
        case BufferUsage::StaticCopy: return GL_STATIC_COPY;
        case BufferUsage::DynamicDraw: return GL_DYNAMIC_DRAW;
        case BufferUsage::DynamicRead: return GL_DYNAMIC_READ;
        case BufferUsage::DynamicCopy: return GL_DYNAMIC_COPY;
    }

    THROW(ArgumentOutOfRangeException{"Invalid buffer usage", "value"});
}

int32_t Graphics::ToOpenGl(const DrawMode value)
{
    switch (value)
    {
        case DrawMode::Points: return GL_POINTS;
        case DrawMode::LineStrip: return GL_LINE_STRIP;
        case DrawMode::LineLoop: return GL_LINE_LOOP;
        case DrawMode::Lines: return GL_LINES;
        case DrawMode::LineStripAdjacency: return GL_LINE_STRIP_ADJACENCY;
        case DrawMode::LinesAdjacency: return GL_LINES_ADJACENCY;
        case DrawMode::TriangleStrip: return GL_TRIANGLE_STRIP;
        case DrawMode::TriangleFan: return GL_TRIANGLE_FAN;
        case DrawMode::Triangles: return GL_TRIANGLES;
        case DrawMode::TriangleStripAdjacency: return GL_TRIANGLE_STRIP_ADJACENCY;
        case DrawMode::TrianglesAdjacency: return GL_TRIANGLES_ADJACENCY;
        case DrawMode::Patches: return GL_PATCHES;
    }

    THROW(ArgumentOutOfRangeException{"Invalid draw mode", "value"});
}

int32_t Graphics::ToOpenGl(const BlendFunction value)
{
    switch (value)
    {
        case BlendFunction::Zero: return GL_ZERO;
        case BlendFunction::One: return GL_ONE;
        case BlendFunction::SrcColor: return GL_SRC_COLOR;
        case BlendFunction::OneMinusSrcColor: return GL_ONE_MINUS_SRC_COLOR;
        case BlendFunction::DstColor: return GL_DST_COLOR;
        case BlendFunction::OneMinusDstColor: return GL_ONE_MINUS_DST_COLOR;
        case BlendFunction::SrcAlpha: return GL_SRC_ALPHA;
        case BlendFunction::OneMinusSrcAlpha: return GL_ONE_MINUS_SRC_ALPHA;
        case BlendFunction::DstAlpha: return GL_DST_ALPHA;
        case BlendFunction::OneMinusDstAlpha: return GL_ONE_MINUS_DST_ALPHA;
        case BlendFunction::ConstantColor: return GL_CONSTANT_COLOR;
        case BlendFunction::OneMinusConstantColor: return GL_ONE_MINUS_CONSTANT_COLOR;
        case BlendFunction::ConstantAlpha: return GL_CONSTANT_ALPHA;
        case BlendFunction::OneMinusConstantAlpha: return GL_ONE_MINUS_CONSTANT_ALPHA;
    }

    THROW(ArgumentOutOfRangeException{"Invalid blend function", "value"});
}

int32_t Graphics::ToOpenGl(const FramebufferType value)
{
    switch (value)
    {
        case FramebufferType::DrawFramebuffer: return GL_DRAW_FRAMEBUFFER;
        case FramebufferType::ReadFramebuffer: return GL_READ_FRAMEBUFFER;
        case FramebufferType::Framebuffer: return GL_FRAMEBUFFER;
    }

    THROW(ArgumentOutOfRangeException{"Invalid blend function", "value"});
}

int32_t Graphics::ToOpenGl(const FramebufferStatus value)
{
    switch (value)
    {
        case FramebufferStatus::Complete: return GL_FRAMEBUFFER_COMPLETE;
        case FramebufferStatus::Undefined: return GL_FRAMEBUFFER_UNDEFINED;
        case FramebufferStatus::IncompleteAttachment: return GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
        case FramebufferStatus::IncompleteMissingAttachment: return GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT;
        case FramebufferStatus::IncompleteDrawBuffer: return GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER;
        case FramebufferStatus::IncompleteReadBuffer: return GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER;
        case FramebufferStatus::Unsupported: return GL_FRAMEBUFFER_UNSUPPORTED;
        case FramebufferStatus::IncompleteMultisample: return GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE;
        case FramebufferStatus::IncompleteLayerTargets: return GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS;
    }

    THROW(ArgumentOutOfRangeException{"Invalid framebuffer status", "value"});
}

int32_t Graphics::ToOpenGl(const FramebufferAttachment value)
{
    switch (value)
    {
        case FramebufferAttachment::Color0: return GL_COLOR_ATTACHMENT0;
        case FramebufferAttachment::Color1: return GL_COLOR_ATTACHMENT1;
        case FramebufferAttachment::Color2: return GL_COLOR_ATTACHMENT2;
        case FramebufferAttachment::Color3: return GL_COLOR_ATTACHMENT3;
        case FramebufferAttachment::Color4: return GL_COLOR_ATTACHMENT4;
        case FramebufferAttachment::Color5: return GL_COLOR_ATTACHMENT5;
        case FramebufferAttachment::Color6: return GL_COLOR_ATTACHMENT6;
        case FramebufferAttachment::Color7: return GL_COLOR_ATTACHMENT7;
        case FramebufferAttachment::Color8: return GL_COLOR_ATTACHMENT8;
        case FramebufferAttachment::Color9: return GL_COLOR_ATTACHMENT9;
        case FramebufferAttachment::Color10: return GL_COLOR_ATTACHMENT10;
        case FramebufferAttachment::Color11: return GL_COLOR_ATTACHMENT11;
        case FramebufferAttachment::Color12: return GL_COLOR_ATTACHMENT12;
        case FramebufferAttachment::Color13: return GL_COLOR_ATTACHMENT13;
        case FramebufferAttachment::Color14: return GL_COLOR_ATTACHMENT14;
        case FramebufferAttachment::Color15: return GL_COLOR_ATTACHMENT15;
        case FramebufferAttachment::Color16: return GL_COLOR_ATTACHMENT16;
        case FramebufferAttachment::Color17: return GL_COLOR_ATTACHMENT17;
        case FramebufferAttachment::Color18: return GL_COLOR_ATTACHMENT18;
        case FramebufferAttachment::Color19: return GL_COLOR_ATTACHMENT19;
        case FramebufferAttachment::Color20: return GL_COLOR_ATTACHMENT20;
        case FramebufferAttachment::Color21: return GL_COLOR_ATTACHMENT21;
        case FramebufferAttachment::Color22: return GL_COLOR_ATTACHMENT22;
        case FramebufferAttachment::Color23: return GL_COLOR_ATTACHMENT23;
        case FramebufferAttachment::Color24: return GL_COLOR_ATTACHMENT24;
        case FramebufferAttachment::Color25: return GL_COLOR_ATTACHMENT25;
        case FramebufferAttachment::Color26: return GL_COLOR_ATTACHMENT26;
        case FramebufferAttachment::Color27: return GL_COLOR_ATTACHMENT27;
        case FramebufferAttachment::Color28: return GL_COLOR_ATTACHMENT28;
        case FramebufferAttachment::Color29: return GL_COLOR_ATTACHMENT29;
        case FramebufferAttachment::Color30: return GL_COLOR_ATTACHMENT30;
        case FramebufferAttachment::Color31: return GL_COLOR_ATTACHMENT31;
        case FramebufferAttachment::Depth: return GL_DEPTH_ATTACHMENT;
        case FramebufferAttachment::Stencil: return GL_STENCIL_ATTACHMENT;
        case FramebufferAttachment::DepthStencil: return GL_DEPTH_STENCIL_ATTACHMENT;
    }

    THROW(ArgumentOutOfRangeException{"Invalid framebuffer attachment", "value"});
}
