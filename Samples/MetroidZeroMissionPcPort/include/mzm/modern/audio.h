#ifndef AUDIO_MODERN
#define AUDIO_MODERN

#include "types.h"
#include "openal/al.h"
#include "openal/alc.h"

#define AUDIO_FILE_COUNT 707

struct AudioData
{
    const char* filename;
    char* data;
    s32 size;
    u16 channels;
    u16 bits;
    s32 frequency;
};

struct AudioModifiers
{
    u8 loop;
    f32 pitch;
    f32 volume;
};

extern ALCdevice* gAudioDevice;
extern ALCcontext* gAudioContext;

extern ALuint gAudioBuffers[AUDIO_FILE_COUNT];
extern s32 gAudioSourceCount;
extern ALuint* gAudioSources;

void InitAudio(void);
void ShutdownAudio(void);

struct AudioData* LoadAudioData(const char* filename);
u8 LoadAudioWAVData(char *fileData, s64 fileSize, struct AudioData *audio);
void UnloadAudioData(struct AudioData* audio);

void ForwardAudio(struct AudioData* audio, const ALuint* buffer, ALuint* source);
ALenum ALFormatFromData(struct AudioData* audio);

u16 IndexFromSound(u16 sound);

s32 SourceFromSound(u16 sound);
// Queues a sound to the next available source. Returns the source index.
// A return value of -1 means all sources are currently being used or an
// error occured while attempting to queue the audio buffer to the source.
s32 SourceQueueSound(u16 sound);

// Checks whether an OpenAL error occured, printing its value if so.
// Returns 1 if an error occured, 0 otherwise.
u8 TestALError(const char* str);

#endif /* AUDIO_MODERN */
