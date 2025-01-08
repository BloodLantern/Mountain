#ifndef SECURITY_LASER_AI_H
#define SECURITY_LASER_AI_H

#ifdef __cplusplus
extern "C"
{
#endif

#define SECURITY_LASER_SMALL 0x2
#define SECURITY_LASER_MEDIUM 0x3
#define SECURITY_LASER_LARGE 0x4
#define SECURITY_LASER_VERY_LARGE 0x5
#define SECURITY_LASER_VERTICAL 0x80

#define SECURITY_LASER_POSE_IDLE 0x9
#define SECURITY_LASER_POSE_DISAPPEARING 0xB
#define SECURITY_LASER_POSE_UNUSED 0xC
#define SECURITY_LASER_POSE_SET_ALARM 0x23

void SecurityLaserInit(void);
void SecurityLaserIdle(void);
void SecurityLaserCheckDespawnAnimEnded(void);
void SecurityLaserSetAlarm(void);
void SecurityLaser_Unused(void);
void SecurityLaser(void);

#ifdef __cplusplus
}
#endif

#endif /* SECURITY_LASER_AI_H */
