/// @file

#pragma once

#include <float.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;

static const u8 U8_MIN = 0;
static const u8 U8_MAX = UINT8_MAX;

typedef uint16_t u16;

static const u16 U16_MIN = 0;
static const u16 U16_MAX = UINT16_MAX;

typedef uint32_t u32;

static const u32 U32_MIN = 0;
static const u32 U32_MAX = UINT32_MAX;

typedef uint64_t u64;

static const u64 U64_MIN = 0;
static const u64 U64_MAX = UINT64_MAX;

typedef size_t usize;

static const usize USIZE_MIN = 0;
static const usize USIZE_MAX = SIZE_MAX;

typedef int8_t i8;

static const i8 I8_MIN = INT8_MIN;
static const i8 I8_MAX = INT8_MAX;

typedef int16_t i16;

static const i16 I16_MIN = INT16_MIN;
static const i16 I16_MAX = INT16_MAX;

typedef int32_t i32;

static const i32 I32_MIN = INT32_MIN;
static const i32 I32_MAX = INT32_MAX;

typedef int64_t i64;

static const i64 I64_MIN = INT64_MIN;
static const i64 I64_MAX = INT64_MAX;

typedef float f32;

static const f32 F32_MIN = FLT_TRUE_MIN;
static const f32 F32_MAX = FLT_MAX;

typedef double f64;

static const f64 F64_MIN = DBL_TRUE_MIN;
static const f64 F64_MAX = DBL_MAX;
