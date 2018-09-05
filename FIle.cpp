#include "File.hpp"

// trim from right, taken from https://stackoverflow.com/a/25829233
inline std::string right_trim(std::string s, const char *t = " \t\n\r\f\v") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

std::string File::get_filename_stripped() const { return right_trim(std::string(filename, 8)); }

std::string File::get_extension_stripped() const { return right_trim(std::string(extension, 3)); }
