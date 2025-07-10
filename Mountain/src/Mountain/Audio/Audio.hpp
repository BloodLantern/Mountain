#pragma once

#include "AL/alext.h"
#include "Mountain/Core.hpp"
#include "Mountain/Containers/Array.hpp"
#include "Mountain/Utils/MetaProgramming.hpp"

/// @namespace Mountain::Audio
/// @brief Low-level audio API
///
/// You should only use this if you know what you are doing and/or have experience with audio APIs such as OpenAL.
namespace Mountain::Audio
{
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

    enum class SourceType : uint8_t
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

    template <typename T>
    concept OpenAlConvertibleT = Meta::IsAny<
        T,
        EventType,
        SourceVector,
        SourceFloat,
        SourceInt,
        SourceBool,
        SourceType,
        ListenerVector,
        ListenerFloat,
        ListenerArray
    >;

    /// @brief Gets the default audio device name
    /// @return Default audio device name
    [[nodiscard]]
    MOUNTAIN_API std::string GetDefaultDeviceName();

    /// @brief Creates an audio source
    /// @return Source id
    [[nodiscard]]
    MOUNTAIN_API uint32_t CreateSource();

    /// @brief Creates multiple audio sources
    /// @return Sources id
    [[nodiscard]]
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

    /// @brief Sets a boolean value for an audio source
    /// @param source Source id
    /// @return Source type
    MOUNTAIN_API SourceType GetSourceType(uint32_t source);

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

    /// @brief Sets the openal event callback
    /// @tparam Size @c events array size
    /// @param events Events to apply the callback to
    /// @param callback Callback function
    template <size_t Size>
    MOUNTAIN_API void SetEventCallback(const Array<EventType, Size>& events, std::function<void(EventType, const std::string&)> callback);

    template <OpenAlConvertibleT T>
    // ReSharper disable once CppFunctionIsNotImplemented
    T FromOpenAl(int32_t value);

    template <>
    MOUNTAIN_API EventType FromOpenAl<EventType>(int32_t value);
    template <>
    MOUNTAIN_API SourceVector FromOpenAl<SourceVector>(int32_t value);
    template <>
    MOUNTAIN_API SourceFloat FromOpenAl<SourceFloat>(int32_t value);
    template <>
    MOUNTAIN_API SourceInt FromOpenAl<SourceInt>(int32_t value);
    template <>
    MOUNTAIN_API SourceBool FromOpenAl<SourceBool>(int32_t value);
    template <>
    MOUNTAIN_API SourceType FromOpenAl<SourceType>(int32_t value);
    template <>
    MOUNTAIN_API ListenerVector FromOpenAl<ListenerVector>(int32_t value);
    template <>
    MOUNTAIN_API ListenerFloat FromOpenAl<ListenerFloat>(int32_t value);
    template <>
    MOUNTAIN_API ListenerArray FromOpenAl<ListenerArray>(int32_t value);
    
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(EventType value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(SourceVector value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(SourceFloat value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(SourceInt value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(SourceBool value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(SourceType value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(ListenerVector value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(ListenerFloat value);
    [[nodiscard]]
    MOUNTAIN_API int32_t ToOpenAl(ListenerArray value);
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
