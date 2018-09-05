#ifndef FAT12_EXTRACTOR_CPP_FAT12ENTRY_HPP
#define FAT12_EXTRACTOR_CPP_FAT12ENTRY_HPP


#include <cstdint>

enum FAT12types : uint16_t {
    FREE = 0x000,
    RESERVED_1 = 0xff0,
    RESERVED_2 = 0xff1,
    RESERVED_3 = 0xff2,
    RESERVED_4 = 0xff3,
    RESERVED_5 = 0xff4,
    RESERVED_6 = 0xff5,
    RESERVED_7 = 0xff6,
    BAD_CLUSTER = 0xff7,
};


#pragma pack(push, 1)

class FAT12Entry {
public:
    inline uint16_t get_first_entry() const { return (wx & static_cast<uint16_t>(0b1111)) << 8 | uv; }

    inline uint16_t get_second_entry() const { return (yz << 4) | ((wx & static_cast<uint16_t>(0b11110000)) >> 4); }

private:
    unsigned char uv;
    unsigned char wx;
    unsigned char yz;
};

#pragma pack(pop)

#endif //FAT12_EXTRACTOR_CPP_FAT12ENTRY_HPP
