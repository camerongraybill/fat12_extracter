#ifndef FAT12_EXTRACTOR_CPP_FILE_HPP
#define FAT12_EXTRACTOR_CPP_FILE_HPP

#include <cstdint>
#include <string>

#pragma pack(push, 1)
enum FileAttributes : uint8_t {
    READ_ONLY = 0b1,
    HIDDEN = 0b10,
    SYSTEM_FILE = 0b100,
    VOLUME_LABEL = 0b1000,
    SUBDIRECTORY = 0b10000,
    ARCHIVE = 0b100000
};

class Time {
public:
    inline uint8_t hour() const { return static_cast<uint8_t>(data >> 11); }

    inline uint8_t minutes() const { return static_cast<uint8_t>((data >> 5) & 0b00111111); }

    inline uint8_t double_seconds() const { return static_cast<uint8_t>(data & 0b00011111); }

private:
    unsigned short data;
};

class Date {
public:
    inline uint16_t year() const { return static_cast<uint16_t>(static_cast<uint8_t>((data >> 9)) + 1980); }

    inline uint8_t month() const { return static_cast<uint8_t>((data >> 5) & 0b00001111); }

    inline uint8_t day() const { return static_cast<uint8_t>(data & 0b00011111); }

private:
    unsigned short data;
};


class File {
public:
    inline const char *get_filename() const { return filename; }

    std::string get_filename_stripped() const;

    inline const char *get_extension() const { return extension; }

    std::string get_extension_stripped() const;

    inline uint8_t get_attribute() const { return attribute; }

    inline const Time &get_time() const { return time; }

    inline const Date &get_date() const { return date; }

    inline unsigned short get_starting_cluster() const { return starting_cluster; }

    inline unsigned int get_file_size() const { return file_size; }

    inline bool is_deleted() const { return static_cast<uint8_t>(filename[0]) == 0xe5; }

private:
    char filename[8];
    char extension[3];
    uint8_t attribute;
    unsigned char reserved[10];
    Time time;
    Date date;
    unsigned short starting_cluster;
    unsigned int file_size;
};

#pragma pack(pop)

#endif //FAT12_EXTRACTOR_CPP_FILE_HPP
