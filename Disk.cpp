#include "Disk.hpp"
#include <fstream>

std::vector<unsigned char> get_all_data(const std::string_view path_to_input_file) {
    // Open the file at the end because we are getting the length
    std::basic_ifstream<unsigned char, std::char_traits<unsigned char> > input_stream{path_to_input_file.data(),
                                                                                      std::ios::binary | std::ios::ate};
    std::ifstream::pos_type length{input_stream.tellg()};
    // Reserve enough data for the full file
    std::vector<unsigned char> raw_data;
    raw_data.resize(length);
    // Read the file
    input_stream.seekg(0, std::ios::beg);
    input_stream.read(raw_data.data(), length);
    input_stream.close();
    return raw_data;
}

Disk::Disk(const std::string_view path_to_input_file) : boot(nullptr), raw_data(get_all_data(path_to_input_file)) {
    // Grab the boot sector data
    boot = reinterpret_cast<BootSector *>(raw_data.data());
    // Grab the FATs
    fat_entries.resize(boot->get_fat_copies_count());
    for (uint8_t i = 0; i < boot->get_fat_copies_count(); i++)
        fat_entries[i] = FAT(cluster(boot->get_reserved_sector_count() + i * boot->get_sectors_per_fat()));
    // Grab the root directory
    uint16_t start_of_root_directory_cluster =
            boot->get_reserved_sector_count() + (boot->get_fat_copies_count() * boot->get_sectors_per_fat());
    root_directory = Directory(cluster(start_of_root_directory_cluster));
    first_data_cluster = static_cast<uint16_t>(start_of_root_directory_cluster +
                                               ((root_directory.length * 32) / (boot->get_bytes_per_sector() *
                                                                                boot->get_sectors_per_cluster())) - 2);
}

Sector Disk::sector(uint16_t sector_num) const { return raw_data.data() + (boot->get_bytes_per_sector() * sector_num); }

Cluster Disk::cluster(uint16_t cluster_num) const { return sector(cluster_num * boot->get_sectors_per_cluster()); }

Cluster Disk::data_cluster(uint16_t cluster_num) const { return cluster(cluster_num + first_data_cluster); }

void Disk::extract_file_to(File const *f, const std::string_view path_to_output_file, bool extract_hidden_files) const {
    if ((f->get_attribute() & FileAttributes::HIDDEN) && !extract_hidden_files) {
        return;
    }
    if (f->get_attribute() & FileAttributes::SUBDIRECTORY) {
        // TODO: Acquire test case for this and implement it
    } else {
        std::basic_ofstream<unsigned char, std::char_traits<unsigned char> > output_stream;
        output_stream.open(path_to_output_file.data(), std::ios::out | std::ios::binary | std::ios::trunc);
        unsigned int remaining_bytes(f->get_file_size());
        auto current_cluster(f->get_starting_cluster());
        while (remaining_bytes > 0) {
            if (remaining_bytes > boot->get_bytes_per_sector() * boot->get_sectors_per_cluster()) {
                output_stream.write(data_cluster(current_cluster),
                                    boot->get_bytes_per_sector() * boot->get_sectors_per_cluster());
                remaining_bytes -= boot->get_bytes_per_sector() * boot->get_sectors_per_cluster();
            } else {
                output_stream.write(data_cluster(current_cluster), remaining_bytes);
                remaining_bytes = 0;
            }
            current_cluster = fat_entries[0][current_cluster];
            // Error handling for different entries in FAT table
            if (((0xff0 <= current_cluster) && (current_cluster <= 0xff6)) || current_cluster == 0xff7) {
                break;
            }
        }
        output_stream.flush();
        output_stream.close();
    }
}