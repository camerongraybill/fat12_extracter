#ifndef FAT12_EXTRACTOR_CPP_UTILS_HPP
#define FAT12_EXTRACTOR_CPP_UTILS_HPP

#include <cstdint>

inline uint16_t swap_endianness(const uint16_t x) {
    constexpr int num = 1;
    // If not little endian, swap
    if (*(char *) &num != 1)
        return (x << 8) | (x >> 8);
    return x;
}

#endif //FAT12_EXTRACTOR_CPP_UTILS_HPP
