#include "process.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cstdint>
#include <iomanip>
#include <filesystem>

using namespace file_hasher;
constexpr std::size_t BLOCK_SIZE = 0x100000;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "ERROR: Invalid input file" << std::endl;
        return 1;
    }

    int input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1) {
        std::cerr << "ERROR: Can't open file " << argv[1] << std::endl;
        return 1;
    }

    data_processor_t processor;
    std::vector<std::uint32_t> block(BLOCK_SIZE);

    std::size_t bytes_read = 0;
    while ((bytes_read = read(input_fd, block.data(), BLOCK_SIZE * sizeof(std::uint32_t))) > 0) {
        std::size_t elems_read = bytes_read / sizeof(std::uint32_t);
        block.resize(elems_read);

        std::uint32_t hash = processor.process_block(block);
        std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << hash << std::endl;
    }

    if (bytes_read == -1) {
        std::cerr << "ERROR: Failed to read from file " <<  argv[1] << std::endl; //TODO
        close(input_fd);
        return 1;
    }

    close(input_fd);
    return 0;
}