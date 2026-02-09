#pragma once

#include <cstdint>

namespace Utils {
    static inline int FastRandInt(int min, int max) {
        static uint64_t x = 0x123456789ABCDEF;
        x ^= x << 7;
        x ^= x >> 9;
        uint64_t r = x * 2685821657736338717ULL;
        return min + (r % (max - min + 1));
    }
}