#include "Directory.hpp"


std::vector<File const *> Directory::iter_files() const {
    std::vector<File const *> retval;
    for (uint16_t i = 0; i < length; i++) {
        auto f(this->operator[](i));
        if (f->is_deleted() || (f->get_attribute() & FileAttributes::VOLUME_LABEL))
            continue;
        retval.push_back(f);
    }
    return retval;
}

inline uint16_t iterate_to_get_length(const File *ptr) {
    const File *iter(ptr);
    while (reinterpret_cast<char const *>(iter)[0] != 0) iter++;
    return static_cast<uint16_t>(iter - ptr);
}


Directory::Directory(const unsigned char *ptr) : Directory(reinterpret_cast<const File *>(ptr)) {}

Directory::Directory(const File *ptr) : files(ptr), length(iterate_to_get_length(ptr)) {}