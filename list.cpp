#include <iostream>

#include "Disk.hpp"

int main(int argc, const char **argv) {
    if (argc != 2)
        std::cerr << "Must be used " + std::string(argv[0]) + " input_file" << std::endl;
    Disk d(argv[1]);
    for (auto const item : d.root_directory.iter_files()) {
        std::cout << item->get_filename_stripped() << "." << item->get_extension_stripped() << " "
        << item->get_file_size() << " bytes Date: " << int(item->get_date().month()) << "-" << int(item->get_date().day()) << "-" << int(item->get_date().year()) << std::endl;
    }
}
