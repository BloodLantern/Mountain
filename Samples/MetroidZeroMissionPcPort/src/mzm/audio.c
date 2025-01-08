#include "mzm/data_audio.h"

u8 gStereoFlag;
struct MusicTrackInfo gMusicTrackInfo;

struct MusicInfo gMusicInfo;

struct TrackData gTrackData0;
struct TrackData gTrackData1;
struct TrackData gTrackData2;
struct TrackData gTrackData3;
struct TrackData gTrackData4;
struct TrackData gTrackData5;
struct TrackData gTrackData6;
struct TrackData gTrackData7;
struct TrackData gTrackData8;

struct SoundChannelBackup gSoundChannelBackup[7];
struct SoundChannelBackup gSoundChannelTrack2Backup[7];
struct SoundQueue gSoundQueue[9];

struct TrackVariables gTrack0Variables[12];
struct TrackVariables gTrack1Variables[10];
struct TrackVariables gTrack2Variables[2];
struct TrackVariables gTrack3Variables[2];
struct TrackVariables gTrack4Variables[2];
struct TrackVariables gTrack5Variables[2];
struct TrackVariables gTrack6Variables[3];
struct TrackVariables gTrack7Variables[1];
struct TrackVariables gTrack8Variables[6];

SoundCodeAFunc_T gSoundCodeAPointer;
u8 gSoundCodeA[1624];
SoundCodeBFunc_T gSoundCodeBPointer;
u8 gSoundCodeB[164];
SoundCodeCFunc_T gSoundCodeCPointer;
u8 gSoundCodeC[176];

struct PSGSoundData gUnk_300376c[1];
struct PSGSoundData gPsgSounds[4];

void UpdateMusic(void)
{

}

void UpdatePsgSounds(void)
{

}

void UpdateTrack(struct TrackData* pTrack)
{

}

void unk_1bf0(struct TrackVariables* pVariables)
{

}

void unk_1c18(struct TrackVariables* pVariables)
{

}

void unk_1c3c(struct TrackVariables* pVariables)
{

}

void unk_1ccc(struct TrackVariables* pVariables, s16 param_2)
{

}

void unk_1d5c(struct TrackVariables* pVariables)
{

}

void unk_1d78(struct TrackVariables* pVariables)
{

}

void unk_1ddc(struct TrackVariables* pVariables)
{

}

void unk_1de8(struct TrackVariables* pVariables)
{

}

void unk_1e2c(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void unk_1f3c(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void unk_1f90(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void unk_1fe0(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void unk_2030(struct PSGSoundData* pSound, struct TrackVariables* pVariables, u32 param_3)
{

}

void unk_20a4(struct SoundChannel* pChannel)
{

}

u16 GetNoteDelay(struct TrackVariables* pVariables, u8 param_2, u8 param_3)
{
    return 0;
}

void AudioCommand_Fine(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void unk_21b0(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void AudioCommand_PatternEnd(struct TrackVariables* pVariables)
{

}

void AudioCommand_Repeat(struct TrackVariables* pVariables)
{

}

void AudioCommand_Priority(struct TrackVariables* pVariables)
{

}

void AudioCommand_KeyShift(struct TrackVariables* pVariables)
{

}

void AudioCommand_Voice(struct TrackData* pTrack, struct TrackVariables* pVariables)
{

}

void AudioCommand_Volume(struct TrackVariables* pVariables)
{

}

void AudioCommand_PanPot(struct TrackVariables* pVariables)
{

}

void AudioCommand_PitchBend(struct TrackVariables* pVariables)
{

}

void AudioCommand_BendRange(struct TrackVariables* pVariables)
{

}

void AudioCommand_LfoSpeed(struct TrackVariables* pVariables)
{

}

void AudioCommand_LfoDelay(struct TrackVariables* pVariables)
{

}

void AudioCommand_ModulationDepth(struct TrackVariables* pVariables)
{

}

void AudioCommand_ModulationType(struct TrackVariables* pVariables)
{

}

void AudioCommand_Tune(struct TrackVariables* pVariables)
{

}

void AudioCommand_ExtendCommand(struct TrackVariables* pVariables)
{

}

void AudioCommand_EndOfTie(struct TrackVariables* pVariables)
{

}

void Music_EmptyCommand(struct TrackVariables* pVariables)
{

}

void ClearRegistersForPsg(struct PSGSoundData* pSound, u8 channel)
{

}

void ClearRegistersForPsg_Unused(struct PSGSoundData* pSound, u8 channel)
{

}
