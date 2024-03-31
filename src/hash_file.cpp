#include "hash_file.hpp"
#include "process.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <stdexcept>

namespace file_hasher {

std::uint32_t hash_file(const std::string& filename) {
    int input_fd = open(filename.data(), O_RDONLY);
    if (input_fd == -1) {
        throw std::runtime_error ("ERROR: Can't open file " + filename);
    }

    data_processor_t processor;
    std::vector<std::uint32_t> block(BLOCK_SIZE);

    std::size_t bytes_read = 0;
    std::uint32_t hash = 0u;
    while ((bytes_read = read(input_fd, block.data(), BLOCK_SIZE * sizeof(std::uint32_t))) > 0) {
        std::size_t elems_read = bytes_read / sizeof(std::uint32_t);
        block.resize(elems_read);

        hash = processor.process_block(block);
    }

    if (bytes_read == -1) {
        close(input_fd);
        throw std::runtime_error ("ERROR: Failed to read from file " + filename);
    }

    close(input_fd);
    return hash;
}

}