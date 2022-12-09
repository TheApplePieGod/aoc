#pragma once

#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <unordered_set>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef int32_t b32;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double d64;
typedef wchar_t wchar;

struct vec2
{
    vec2() = default;
    vec2(f32 _x, f32 _y)
        : x(_x), y(_y)
    {}
    vec2(int _x, int _y)
        : x(static_cast<f32>(_x)), y(static_cast<f32>(_y))
    {}

    f32 x = 0.f;
    f32 y = 0.f;
};

struct vec2i
{
    vec2i() = default;
    vec2i(int _x, int _y)
        : x(_x), y(_y)
    {}
    vec2i(f32 _x, f32 _y)
        : x(static_cast<int>(_x)), y(static_cast<int>(_y))
    {}
    
    int x = 0;
    int y = 0;
};