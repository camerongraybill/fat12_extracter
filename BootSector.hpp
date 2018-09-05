#ifndef FAT12_EXTRACTOR_CPP_BOOTSECTOR_HPP
#define FAT12_EXTRACTOR_CPP_BOOTSECTOR_HPP


#include <cstdint>
#include "utils.hpp"

enum MediaDescriptor : uint8_t {
    FLOPPY = 0xf0,
    HARD_DISK = 0xf8
};
#pragma pack(push, 1)

struct BootSector {

    inline const unsigned char *get_oem_name_and_version() const { return oem_name_and_version; }

    inline unsigned short get_bytes_per_sector() const { return swap_endianness(bytes_per_sector); }

    inline uint8_t get_sectors_per_cluster() const { return sectors_per_cluster; }

    inline unsigned short get_reserved_sector_count() const { return swap_endianness(reserved_sector_count); }

    inline uint8_t get_fat_copies_count() const { return fat_copies_count; }

    inline unsigned short get_root_directory_entry_count() const { return swap_endianness(root_directory_entry_count); }

    inline unsigned short get_sectors_count() const { return swap_endianness(sectors_count); }

    inline MediaDescriptor get_media() const { return media; }

    inline unsigned short get_sectors_per_fat() const { return swap_endianness(sectors_per_fat); }

    inline unsigned short get_sectors_per_track() const { return swap_endianness(sectors_per_track); }

    inline unsigned short get_head_count() const { return swap_endianness(head_count); }

    inline unsigned short get_hidden_sector_count() const { return swap_endianness(hidden_sector_count); }

private:
    /* 0-2 */
    uint8_t bootstrap_loc[3];
    /* 3-10 */
    unsigned char oem_name_and_version[8];
    /* 11-12 */
    unsigned short bytes_per_sector;
    /* 13 */
    uint8_t sectors_per_cluster;
    /* 14-15 */
    unsigned short reserved_sector_count;
    /* 16 */
    uint8_t fat_copies_count;
    /* 17-18 */
    unsigned short root_directory_entry_count;
    /* 19-20 */
    unsigned short sectors_count;
    /* 21 */
    MediaDescriptor media;
    /* 22-23 */
    unsigned short sectors_per_fat;
    /* 24-25 */
    unsigned short sectors_per_track;
    /* 26-27 */
    unsigned short head_count;
    /* 28-29 */
    unsigned short hidden_sector_count;
    /* 30-509 */
    unsigned char bootstrap[480];
    /* 510-511 */
    uint8_t hex_55;
    uint8_t hex_aa;
};

#pragma pack(pop)

#endif //FAT12_EXTRACTOR_CPP_BOOTSECTOR_HPP
