#include "algorithms.hpp"

uint32_t algo1()
{
    return 7;
}

uint16_t algo2(uint32_t process)
{
    return static_cast<uint16_t>(((process >> 16) & 0xfFFF) ^ process);
}
