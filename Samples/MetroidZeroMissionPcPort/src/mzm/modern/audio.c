#include "modern/audio.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <io.h>

#include "openal/alext.h"

ALCdevice* gAudioDevice;
ALCcontext* gAudioContext;

ALuint gAudioBuffers[AUDIO_FILE_COUNT];
s32 gAudioSourceCount;
ALuint* gAudioSources;

s32 gAudioSoundSource[AUDIO_FILE_COUNT];

void InitAudio(void)
{
	if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_FALSE)
		printf("Enumeration extension not available\n");

	gAudioDevice = alcOpenDevice(alcGetString(NULL, ALC_DEFAULT_DEVICE_SPECIFIER));
	if (!gAudioDevice)
    {
		printf("Unable to open default audio device\n");
        return;
    }

	printf("Using audio device: %s\n", alcGetString(gAudioDevice, ALC_DEVICE_SPECIFIER));

	gAudioContext = alcCreateContext(gAudioDevice, NULL);
	if (!alcMakeContextCurrent(gAudioContext))
    {
		printf("Failed to create audio context\n");
		return;
	}

    {
        int size;
        alcGetIntegerv(gAudioDevice, ALC_ATTRIBUTES_SIZE, 1, &size);
        ALCint* attributes = malloc(size * sizeof(ALCint));
        alcGetIntegerv(gAudioDevice, ALC_ALL_ATTRIBUTES, size, attributes);

        for (int i = 0; i < size; i++)
        {
            if (attributes[i] == ALC_MONO_SOURCES || attributes[i] == ALC_STEREO_SOURCES)
                gAudioSourceCount += attributes[i + 1];
        }

        free(attributes);

        gAudioSources = malloc(gAudioSourceCount * sizeof(ALuint));
    }

    alGenBuffers(AUDIO_FILE_COUNT, gAudioBuffers);
    TestALError("alGenBuffers");

    alGenSources(gAudioSourceCount, gAudioSources);
    TestALError("alGenSources");

    for (s32 i = 0; i < AUDIO_FILE_COUNT; i++)
        gAudioSoundSource[i] = -1;

    for (s32 i = 0; i < AUDIO_FILE_COUNT; i++)
    {
        char buffer[18];
        sprintf(buffer, "audio/song%03d.wav", i);

        if (_access(buffer, 0) != 0)
            continue;

        struct AudioData* data = LoadAudioData(buffer);

        ForwardAudio(data, &gAudioBuffers[i], &gAudioSources[i]);

        UnloadAudioData(data);
    }
}

void ShutdownAudio(void)
{
    alDeleteSources(gAudioSourceCount, gAudioSources);
    TestALError("alDeleteSources");
    alDeleteBuffers(AUDIO_FILE_COUNT, gAudioBuffers);
    TestALError("alDeleteBuffers");

    free(gAudioSources);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(gAudioContext);
    alcCloseDevice(gAudioDevice);
}

struct AudioData* LoadAudioData(const char* filename)
{
    struct AudioData* audioData = malloc(sizeof(struct AudioData));
    audioData->filename = filename;

    FILE* file;
    fopen_s(&file, filename, "rb");
    if (file == NULL)
    {
        printf("Could not open file %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    s32 fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* fileData = _malloca(fileSize);
    fread(fileData, sizeof(char), fileSize, file);

    fclose(file);

    u8 error = 0;

    char format[5] = { 0 };
    memcpy(format, &fileData[0], 4);
    if (strcmp(format, "RIFF") == 0)
    {
        if (LoadAudioWAVData(fileData, fileSize, audioData))
        {
            error = 1;
            printf("Invalid WAV file content\n");
        }
    }
    else
    {
        error = 1;
        printf("Invalid file specification %s\n", format);
    }

    if (error)
    {
        _freea(fileData);
        free(audioData);
        printf("An error occurred while trying to load audio file: %s\n", filename);
        return NULL;
    }
    else
    {
        return audioData;
    }
}

u8 LoadAudioWAVData(char* fileData, s64 fileSize, struct AudioData* audio)
{
    u32 filePos = 8; // Starting at 8 because the RIFF header contains the 4 characters "RIFF" and a 32-bit integer for the size of the file
    char str[5] = { 0 };

    memcpy(str, &fileData[filePos], 4);
    if (strcmp(str, "WAVE") != 0)
    {
        printf("Invalid WAV file header: %s, expected 'WAVE'\n", str);
        return 1;
    }
    filePos += 4;

    for (; strcmp(str, "fmt ") != 0 && filePos < fileSize; filePos++)
        memcpy(str, &fileData[filePos], 4);
    filePos += 9;

    memcpy(&audio->channels, &fileData[filePos], sizeof(short));
    filePos += sizeof(short);

    memcpy(&audio->frequency, &fileData[filePos], sizeof(int));
    filePos += 10;

    memcpy(&audio->bits, &fileData[filePos], sizeof(short));
    filePos += sizeof(short);

    for (; strcmp(str, "data") != 0 && filePos < fileSize; filePos++)
        memcpy(str, &fileData[filePos], 4);
    filePos += 3;

    memcpy(&audio->size, &fileData[filePos], sizeof(int));
    filePos += sizeof(int);

    audio->data = malloc(audio->size);
    memcpy(audio->data, &fileData[filePos], audio->size);

    return 0;
}

void UnloadAudioData(struct AudioData* audio)
{
    if (audio == NULL)
        return;

    free(audio->data);
    free(audio);
}

void ForwardAudio(struct AudioData* audio, const ALuint* buffer, ALuint* source)
{
    if (audio == NULL)
        return;

    alBufferData(*buffer, ALFormatFromData(audio), audio->data, audio->size, audio->frequency);
    TestALError("alBufferData");
}

ALenum ALFormatFromData(struct AudioData *audio)
{
    ALenum format = 0;
    if (audio->channels == 1)
    {
        switch (audio->bits)
        {
            case 8:
                format = AL_FORMAT_MONO8;
                break;
            case 16:
                format = AL_FORMAT_MONO16;
                break;
            case 32:
                format = AL_FORMAT_MONO_FLOAT32;
                break;
            case 64:
                format = AL_FORMAT_MONO_DOUBLE_EXT;
                break;
        }
    }
    else if (audio->channels == 2)
    {
        switch (audio->bits)
        {
            case 8:
                format = AL_FORMAT_STEREO8;
                break;
            case 16:
                format = AL_FORMAT_STEREO16;
                break;
            case 32:
                format = AL_FORMAT_STEREO_FLOAT32;
                break;
            case 64:
                format = AL_FORMAT_STEREO_DOUBLE_EXT;
                break;
        }
    }

    if (format == 0)
        printf("Unsupported number of channels %d or bits %d\n", audio->channels, audio->bits);

    return format;
}

u16 IndexFromSound(u16 sound)
{
    return sound - 1;
}

s32 SourceFromSound(u16 sound)
{
    return gAudioSoundSource[IndexFromSound(sound)];
}

s32 SourceQueueSound(u16 sound)
{
    for (s32 i = 0; i < gAudioSourceCount; i++)
    {
        ALint state;
        alGetSourcei(gAudioSources[i], AL_SOURCE_STATE, &state);

        if (state == AL_INITIAL || state == AL_STOPPED)
        {
            s32 soundIndex = IndexFromSound(sound);
            alSourceQueueBuffers(gAudioSources[i], 1, &gAudioBuffers[soundIndex]);
            if (TestALError("SourceQueueSound"))
                return -1;

            gAudioSoundSource[soundIndex] = i;

            return i;
        }
    }

    return -1;
}

u8 TestALError(const char* str)
{
    ALenum error = alGetError();

    if (error == AL_NO_ERROR)
        return 0;

    printf("AL Error: %s, str: %s\n", alGetString(error), str);

    return 1;
}
