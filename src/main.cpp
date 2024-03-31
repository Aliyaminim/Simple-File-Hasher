#include "process.hpp"
#include "hash_file.hpp"
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <stdexcept>

using namespace file_hasher;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: Invalid input file" << std::endl;
        return 1;
    }

    std::uint32_t hash = 0u;
    try {
        hash = hash_file(argv[1]);
    }
    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << hash << std::endl;
    return 0;
}