#pragma once

#include "AL/alext.h"
#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @namespace Mountain::Audio
/// @brief Low-level audio API
///
/// You should only use this if you know what you are doing and/or have experience with audio APIs such as OpenAL.
/// If you are looking for the audio utility functions, refer to @c Mountain::Sound
namespace Mountain::Audio
{
#pragma region Enums
    enum class Error : uint8_t
    {
        None,
        InvalidName,
        InvalidEnum,
        InvalidValue,
        InvalidOperation,
        OutOfMemory,
    };

    enum class ContextError : uint8_t
    {
        None,
        InvalidDevice,
        InvalidContext,
        InvalidEnum,
        InvalidValue,
        OutOfMemory
    };

    enum class EventType : uint8_t
    {
        DeviceChanged,
        DeviceAdded,
        DeviceRemoved,
    };

    enum class SourceVector : uint8_t
    {
        Direction,
        Position,
        Velocity
    };

    enum class SourceFloat : uint8_t
    {
        ConeInnerAngle,
        ConeOuterAngle,
        ConeOuterGain,
        Gain,
        MaxDistance,
        MaxGain,
        MinGain,
        Pitch,
        ReferenceDistance,
        RollOffFactor,
        SecondsOffset
    };

    enum class SourceInt : uint8_t
    {
        Buffer,
        ByteOffset,
        SampleOffset,
        SourceType
    };

    enum class SourceBool : uint8_t
    {
        Looping,
        SourceRelative
    };

    enum class SourcePlayType : uint8_t
    {
        Static,
        Streaming,
        Undetermined
    };

    enum class ListenerVector : uint8_t
    {
        Position,
        Velocity
    };

    enum class ListenerFloat : uint8_t
    {
        Gain
    };

    enum class ListenerArray : uint8_t
    {
        Orientation
    };

    enum class SourceType : uint8_t
    {
        Mono,
        Stereo
    };

    enum class ContextAttribute : uint8_t
    {
        Frequency,
        RefreshRate,
        Sync,
        MonoSourceAmount,
        StereoSourceAmount
    };

    enum class SourceState : uint8_t
    {
        Initial,
        Playing,
        Paused,
        Stopped
    };

    enum class BufferInt : uint8_t
    {
        Bits,
        Channels,
        Frequency,
        Size
    };
    
    enum class BufferFormat : uint8_t
    {
        Unknown,
        Mono8,
        Mono16,
        MonoFloat32,
        MonoDouble,
        Stereo8,
        Stereo16,
        StereoFloat32,
        StereoDouble,
    };

    template <typename T>
    concept OpenAlConvertibleT = Meta::IsAny<
        T,
        Error,
        ContextError,
        EventType,
        SourceVector,
        SourceFloat,
        SourceInt,
        SourceBool,
        SourcePlayType,
        ListenerVector,
        ListenerFloat,
        ListenerArray,
        SourceType,
        ContextAttribute,
        SourceState,
        BufferInt,
        BufferFormat
    >;
#pragma endregion Enums

#pragma region Source
    /// @brief Creates an audio source
    /// @return Source id
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API uint32_t CreateSource();

    /// @brief Creates multiple audio sources
    /// @param count Amount of sources
    /// @return Sources id
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API List<uint32_t> CreateSources(size_t count);

    /// @brief Deletes an audio source
    /// @param source Source id
    MOUNTAIN_API void DeleteSource(uint32_t source);

    /// @brief Deletes multiple audio sources
    /// @param sources Sources id
    MOUNTAIN_API void DeleteSources(const List<uint32_t>& sources);

    /// @brief Plays an audio source
    /// @param source Source id
    MOUNTAIN_API void PlaySource(uint32_t source);

    /// @brief Pauses an audio source
    /// @param source Source id
    MOUNTAIN_API void PauseSource(uint32_t source);

    /// @brief Stops an audio source
    /// @param source Source id
    MOUNTAIN_API void StopSource(uint32_t source);
    
    /// @brief Rewinds an audio source
    /// @param source Source id
    MOUNTAIN_API void RewindSource(uint32_t source);

    /// @brief Sets a vector value for an audio source
    /// @param source Source id
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetSourceVector(uint32_t source, SourceVector type, const Vector3& value);

    /// @brief Sets a float value for an audio source
    /// @param source Source id
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetSourceFloat(uint32_t source, SourceFloat type, float_t value);

    /// @brief Sets an int value for an audio source
    /// @param source Source id
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetSourceInt(uint32_t source, SourceInt type, int32_t value);

    /// @brief Sets a boolean value for an audio source
    /// @param source Source id
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetSourceBool(uint32_t source, SourceBool type, bool_t value);

    /// @brief Gets the play type of a source
    /// @param source Source id
    /// @return Source play type
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourcePlayType GetSourceType(uint32_t source);

    /// @brief Gets the state of a source
    /// @param source Source id
    /// @return Source state
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceState GetSourceState(uint32_t source);

#pragma endregion Source

#pragma region Listener
    /// @brief Sets a vector value for an audio listener
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetListenerVector(ListenerVector type, const Vector3& value);

    /// @brief Sets a float value for an audio listener
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetListenerFloat(ListenerFloat type, float_t value);

    /// @brief Sets an array value for an audio listener
    /// @param type Value type
    /// @param value Value
    MOUNTAIN_API void SetListenerArray(ListenerArray type, const Array<Vector3, 2>& value);
#pragma endregion Listener

#pragma region Buffer
    /// @brief Creates a buffer
    /// @return Buffer id
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API uint32_t CreateBuffer();

    /// @brief Creates a buffer
    /// @param count Amount of buffers
    /// @return Buffers id
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API List<uint32_t> CreateBuffers(size_t count);

    /// @brief Sets the data for a buffer
    /// @param buffer Buffer id
    /// @param format Buffer format
    /// @param data Data
    /// @param length Data length
    /// @param sampleRate Sample rate
    MOUNTAIN_API void SetBufferData(uint32_t buffer, BufferFormat format, const void* data, size_t length, int32_t sampleRate);

    /// @brief Gets an integer value of a buffer
    /// @param buffer Buffer id
    /// @param type Value type
    /// @return Value
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t GetBufferInt(uint32_t buffer, BufferInt type);
    
    /// @brief Deletes a buffer
    /// @param buffer Buffer id
    MOUNTAIN_API void DeleteBuffer(uint32_t buffer);

    /// @brief Delets buffers
    /// @param buffers Buffers id
    MOUNTAIN_API void DeleteBuffers(const List<uint32_t>& buffers);

    /// @brief Gets the format of a buffer
    /// @param channels Number of channels
    /// @param bitDepth Bit depth
    /// @return Format
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API BufferFormat GetBufferFormat(uint16_t channels, uint16_t bitDepth);
#pragma endregion Buffer

#pragma region Device
    /// @brief Gets the default audio device name
    /// @return Default audio device name
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string GetDefaultDeviceName();

    /// @brief Gets a list of all the devices available
    /// @return List of devices names
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API void GetAllDevices(List<std::string>& devices);

    /// @brief Opens an audio device
    /// @param name Device name
    /// @return Opened device
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ALCdevice* OpenDevice(const std::string& name);

    /// @brief Closes an audio device
    /// @param device Audio device
    MOUNTAIN_API void CloseDevice(ALCdevice* device);

    /// @brief Re-pens an audio device
    /// @param device Device
    /// @param newName Device name
    MOUNTAIN_API void ReopenDevice(ALCdevice* device, const std::string& newName);
    
    /// @brief Gets the attributes of an audio device context
    /// @param device Audio device
    /// @param attributes Attributes, written to
    MOUNTAIN_API void GetDeviceAttributes(ALCdevice* device, List<int32_t>& attributes);

    /// @brief Gets a requested attributes from a list
    /// @param attributes Attribute list
    /// @param attribute Attribute
    /// @return Attribute value
    MOUNTAIN_API int32_t GetDeviceAttribute(const List<int32_t>& attributes, ContextAttribute attribute);
#pragma endregion Device

#pragma region Misc
    /// @brief Gets the latest OpenAl error
    /// @return Error
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Error GetError();

    /// @brief Gets the string representing an error
    /// @param error Error
    /// @return String
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string_view GetErrorString(Error error);

    /// @brief Gets the latest OpenAl context error
    /// @param device Device
    /// @return Error
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ContextError GetContextError(ALCdevice* device);

    /// @brief Gets the string representing a context error
    /// @param device
    /// @param error Error
    /// @return String
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API std::string_view GetContextErrorString(ALCdevice* device, ContextError error);

    /// @brief Sets the openal event callback
    /// @tparam Size @c events array size
    /// @param events Events to apply the callback to
    /// @param callback Callback function
    template <size_t Size>
    void SetEventCallback(const Array<EventType, Size>& events, std::function<void(EventType, const std::string&)> callback);
#pragma endregion Misc

#pragma region Context
    /// @brief Creates an audio context
    /// @param device Audio device
    /// @return Context
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ALCcontext* CreateContext(ALCdevice* device);

    /// @brief Destroys the audio context
    /// @param context Context
    MOUNTAIN_API void DestroyContext(ALCcontext* context);
    
    /// @brief Sets the current audio context
    /// @param context Context
    MOUNTAIN_API void SetContext(ALCcontext* context);
#pragma endregion Context

#pragma region Converters
    template <OpenAlConvertibleT T>
    // ReSharper disable once CppFunctionIsNotImplemented
    T FromOpenAl(int32_t value);

    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API EventType FromOpenAl<EventType>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceVector FromOpenAl<SourceVector>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceFloat FromOpenAl<SourceFloat>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceInt FromOpenAl<SourceInt>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceBool FromOpenAl<SourceBool>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourcePlayType FromOpenAl<SourcePlayType>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ListenerVector FromOpenAl<ListenerVector>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ListenerFloat FromOpenAl<ListenerFloat>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ListenerArray FromOpenAl<ListenerArray>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API Error FromOpenAl<Error>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ContextError FromOpenAl<ContextError>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API ContextAttribute FromOpenAl<ContextAttribute>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API SourceState FromOpenAl<SourceState>(int32_t value);
    template <>
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API BufferFormat FromOpenAl<BufferFormat>(int32_t value);
    
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(EventType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourceVector value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourceFloat value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourceInt value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourceBool value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourcePlayType value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(ListenerVector value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(ListenerFloat value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(ListenerArray value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(Error value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(ContextError value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(ContextAttribute value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(SourceState value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(BufferInt value);
    ATTRIBUTE_NODISCARD
    MOUNTAIN_API int32_t ToOpenAl(BufferFormat value);
#pragma endregion Converters
}

// Start of Audio.hpp

namespace Mountain::Audio
{
    template <size_t Size>
    void SetEventCallback(
        [[maybe_unused]] const Array<EventType, Size>& events,
        [[maybe_unused]] const std::function<void(EventType, const std::string&)> callback
    )
    {
        // We can't use callback directly in the lambda below, since a lambda can only be converted to a function pointer
        // if it doesn't capture anything, so copy it statically here first and use that
        static decltype(callback)& callbackDup = callback;

        const Array<int32_t, Size> eventsAl = events.Select([](const EventType& type) -> int32_t { return ToOpenAl(type); });
        alcEventControlSOFT(Size, eventsAl.GetData(), true);
        alcEventCallbackSOFT([](const ALCenum eventType,
            ALCenum,
            ALCdevice*,
            ALCsizei,
            const ALCchar* message,
            void*)
        {
            callbackDup(FromOpenAl<EventType>(eventType), message);
        }, nullptr);
    }
}
