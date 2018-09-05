#ifndef FAT12_EXTRACTOR_CPP_FAT_HPP
#define FAT12_EXTRACTOR_CPP_FAT_HPP


#include "FAT12Entry.hpp"

class FAT {
public:
    FAT() = default;

    inline explicit FAT(const unsigned char *ptr) : FAT(reinterpret_cast<const FAT12Entry *>(ptr)) {}

    inline explicit FAT(const FAT12Entry *ptr) : entries(ptr) {}

    FAT(const FAT &) = default;

    inline uint16_t get_value(uint16_t at) const {
        return at % 2 == 0 ? entries[at / 2].get_first_entry() : entries[(at - 1) / 2].get_second_entry();
    }

    inline uint16_t operator[](uint16_t x) const { return get_value(x); }

private:
    const FAT12Entry *entries = nullptr;
};


#endif //FAT12_EXTRACTOR_CPP_FAT_HPP
