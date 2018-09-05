cmake_minimum_required(VERSION 3.12)
project(fat12_extractor_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(extract extract.cpp BootSector.hpp utils.hpp FAT12Entry.hpp Disk.cpp Disk.hpp File.hpp FAT.hpp Directory.cpp Directory.hpp File.cpp)
add_executable(list BootSector.hpp utils.hpp FAT12Entry.hpp Disk.cpp Disk.hpp File.hpp FAT.hpp Directory.cpp Directory.hpp File.cpp list.cpp)