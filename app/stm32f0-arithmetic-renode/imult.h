#pragma once
#include <cstdint>

uint32_t imultU32ByU32ToU32Arm32(uint32_t a, uint32_t b);

template<bool useBuiltinAddOverflow = true>
uint64_t imultU32ByU32ToU64(uint32_t a, uint32_t b);

uint64_t imultU32ByU32ToU64Arm32(uint32_t a, uint32_t b);

int64_t imultI32ByI32ToI64(int32_t a, int32_t b);

int64_t imultI32ByI32ToI64Arm32(int32_t a, int32_t b);
