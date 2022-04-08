/// @file

#pragma once

#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;

static const u8 U8_MIN = 0;
static const u8 U8_MAX = UINT8_MAX;

static inline u8 u8_min(const u8 a, const u8 b) {
    return (a < b) ? a : b;
}

static inline u8 u8_max(const u8 a, const u8 b) {
    return (a > b) ? a : b;
}

typedef uint16_t u16;

static const u16 U16_MIN = 0;
static const u16 U16_MAX = UINT16_MAX;

static inline u16 u16_min(const u16 a, const u16 b) {
    return (a < b) ? a : b;
}

static inline u16 u16_max(const u16 a, const u16 b) {
    return (a > b) ? a : b;
}

typedef uint32_t u32;

static const u32 U32_MIN = 0;
static const u32 U32_MAX = UINT32_MAX;

static inline u32 u32_min(const u32 a, const u32 b) {
    return (a < b) ? a : b;
}

static inline u32 u32_max(const u32 a, const u32 b) {
    return (a > b) ? a : b;
}

typedef uint64_t u64;

static const u64 U64_MIN = 0;
static const u64 U64_MAX = UINT64_MAX;

static inline u64 u64_min(const u64 a, const u64 b) {
    return (a < b) ? a : b;
}

static inline u64 u64_max(const u64 a, const u64 b) {
    return (a > b) ? a : b;
}

typedef size_t usize;

static const usize USIZE_MIN = 0;
static const usize USIZE_MAX = SIZE_MAX;

static inline usize usize_min(const usize a, const usize b) {
    return (a < b) ? a : b;
}

static inline usize usize_max(const usize a, const usize b) {
    return (a > b) ? a : b;
}

typedef int8_t i8;

static const i8 I8_MIN = INT8_MIN;
static const i8 I8_MAX = INT8_MAX;

static inline i8 i8_min(const i8 a, const i8 b) {
    return (a < b) ? a : b;
}

static inline i8 i8_max(const i8 a, const i8 b) {
    return (a > b) ? a : b;
}

typedef int16_t i16;

static const i16 I16_MIN = INT16_MIN;
static const i16 I16_MAX = INT16_MAX;

static inline i16 i16_min(const i16 a, const i16 b) {
    return (a < b) ? a : b;
}

static inline i16 i16_max(const i16 a, const i16 b) {
    return (a > b) ? a : b;
}

typedef int32_t i32;

static const i32 I32_MIN = INT32_MIN;
static const i32 I32_MAX = INT32_MAX;

static inline i32 i32_min(const i32 a, const i32 b) {
    return (a < b) ? a : b;
}

static inline i32 i32_max(const i32 a, const i32 b) {
    return (a > b) ? a : b;
}

typedef int64_t i64;

static const i64 I64_MIN = INT64_MIN;
static const i64 I64_MAX = INT64_MAX;

static inline i64 i64_min(const i64 a, const i64 b) {
    return (a < b) ? a : b;
}

static inline i64 i64_max(const i64 a, const i64 b) {
    return (a > b) ? a : b;
}

typedef float f32;

static const f32 F32_MIN = FLT_TRUE_MIN;
static const f32 F32_MAX = FLT_MAX;

static inline f32 f32_min(const f32 a, const f32 b) {
    return (a < b) ? a : b;
}

static inline f32 f32_max(const f32 a, const f32 b) {
    return (a > b) ? a : b;
}

typedef double f64;

static const f64 F64_MIN = DBL_TRUE_MIN;
static const f64 F64_MAX = DBL_MAX;

static inline f64 f64_min(const f64 a, const f64 b) {
    return (a < b) ? a : b;
}

static inline f64 f64_max(const f64 a, const f64 b) {
    return (a > b) ? a : b;
}
