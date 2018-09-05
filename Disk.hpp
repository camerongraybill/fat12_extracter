#ifndef FAT12_EXTRACTOR_CPP_DISK_HPP
#define FAT12_EXTRACTOR_CPP_DISK_HPP


#include <string>
#include <string_view>
#include "File.hpp"
#include "FAT.hpp"
#include "BootSector.hpp"
#include "Directory.hpp"
#include <vector>

typedef unsigned const char *Sector;
typedef unsigned const char *Cluster;

class Disk {
public:
    explicit Disk(std::string_view path_to_input_file);

    BootSector *boot;
    std::vector<FAT> fat_entries;
    Directory root_directory;

    void extract_file_to(File const *f, std::string_view path_to_output_file, bool extract_hidden_files = false) const;

private:
    Sector sector(uint16_t) const;

    Cluster cluster(uint16_t) const;

    Cluster data_cluster(uint16_t) const;

    uint16_t first_data_cluster;
    std::vector<unsigned char> raw_data;
};


#endif //FAT12_EXTRACTOR_CPP_DISK_HPP
