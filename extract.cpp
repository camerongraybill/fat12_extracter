#include <iostream>

#include "Disk.hpp"

int main(int argc, const char **argv) {
    if (argc != 3)
        std::cerr << "Must be used " + std::string(argv[0]) + " input_file output_folder" << std::endl;
    Disk d(argv[1]);
    std::string output_folder(argv[2]);
    for (auto const item : d.root_directory.iter_files()) {
        d.extract_file_to(item, output_folder + item->get_filename_stripped() + "." + item->get_extension_stripped());
    }
}
