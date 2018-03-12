// (C) Copyright 2018 Greg Whiteley. All Rights Reserved.
#pragma once

#include <stdint.h>

inline constexpr uint32_t bit32(unsigned bit)
{
    return 1 << bit;
}

inline constexpr uint32_t mask32_(unsigned bit)
{
    return bit >= 31 ? 0xFFFFFFFFU : ((1U << (bit + 1)) - 1);
}

inline constexpr uint32_t mask32(unsigned top, unsigned bottom)
{
    return mask32_(top) - (bottom == 0 ? 0 : mask32_(bottom - 1));
}
