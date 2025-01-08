#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

#define TRUE 1
#define FALSE 0
#define NULL ((void *)0)

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
typedef double f64;
typedef unsigned long long u64;
typedef signed long long s64;
typedef volatile unsigned char vu8;
typedef volatile signed char vs8;
typedef volatile unsigned short vu16;
typedef volatile signed short vs16;
typedef volatile unsigned int vu32;
typedef volatile signed int vs32;
typedef volatile float vf32;
typedef volatile double vf64;
typedef volatile unsigned long long vu64;
typedef volatile signed long long vs64;

#define SCHAR_MIN ((s8)-0x80)
#define SCHAR_MAX ((s8)0x7F)
#define UCHAR_MAX ((u8)0xFF)

#define SHORT_MIN ((s16)-0x8000)
#define SHORT_MAX ((s16)0x7FFF)
#define USHORT_MAX ((u16)0xFFFF)

#define INT_MIN (-0x80000000)
#define INT_MAX (0x7FFFFFFF)
#define UINT_MAX ((u32)0xFFFFFFFF)

#define SUB_PIXEL_RATIO 4
#define SUB_PIXEL_NUMBER 16

#define BLOCK_SIZE (SUB_PIXEL_NUMBER * SUB_PIXEL_RATIO)
#define HALF_BLOCK_SIZE (BLOCK_SIZE / 2)
#define QUARTER_BLOCK_SIZE (BLOCK_SIZE / 4)
#define EIGHTH_BLOCK_SIZE (BLOCK_SIZE / 8)
#define PIXEL_SIZE (BLOCK_SIZE / SUB_PIXEL_NUMBER)
#define BLOCK_POSITION_FLAG ((u16)~BLOCK_SIZE + ONE_SUB_PIXEL)
#define SUB_PIXEL_POSITION_FLAG (BLOCK_SIZE - ONE_SUB_PIXEL)
#define ONE_SUB_PIXEL (PIXEL_SIZE / PIXEL_SIZE)

#define SCREEN_SIZE_X 240
#define SCREEN_SIZE_Y 160

struct RawCoordsX {
    u16 x;
    u16 y;
};

struct RawCoordsY {
    u16 y;
    u16 x;
};

typedef void (*Func_T)(void);

#ifdef __cplusplus
}
#endif

#endif /* TYPES_H */
