#ifndef FAT12_EXTRACTOR_CPP_DIRECTORY_HPP
#define FAT12_EXTRACTOR_CPP_DIRECTORY_HPP

#include "File.hpp"
#include <cstdint>
#include <vector>
#include <algorithm>


class Directory {
public:
    Directory() = default;

    explicit Directory(const unsigned char *ptr);

    explicit Directory(const File *ptr);

    const File *operator[](uint16_t pos) const { return files + pos; }

    uint16_t length{0};

    std::vector<File const *> iter_files() const;

private:

    const File *files = nullptr;
};


#endif //FAT12_EXTRACTOR_CPP_DIRECTORY_HPP
