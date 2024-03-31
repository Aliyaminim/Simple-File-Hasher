#include <iostream>
#include <iostream>
#include <fstream>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <iomanip>
#include <stdexcept>
#include "hash_file.hpp"

using namespace file_hasher;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "ERROR: Invalid input file" << std::endl;
        return 1;
    }

    const int NUM_FILES = argc - 1;
    const std::size_t HASH_SIZE = sizeof(std::uint32_t) * NUM_FILES;

    int shm_fd = shm_open("/hash_mem", O_CREAT | O_RDWR, 0666);
    if (ftruncate(shm_fd, HASH_SIZE) == -1) {
        std::cerr << "ERROR: Truncating failed" << std::endl;
        close(shm_fd);
        shm_unlink("/hash_mem");
        return 1;
    }

    std::uint32_t* shared_memory = (std::uint32_t*) mmap(0, HASH_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    pid_t pid;
    for (int i = 0; i < NUM_FILES; ++i) {
        pid = fork();
        if (pid < 0) {
            std::cerr << "ERROR: Can't fork process" << std::endl;
            return 1;
        } else if (pid == 0) {
            // Child process
            std::uint32_t hash = hash_file(argv[i + 1]);
            shared_memory[i] = hash;
            _exit(0);
        }
    }

    waitpid(-1, NULL, 0);

    std::uint32_t result_hash = 0u;
    for (int i = 0; i < NUM_FILES; ++i) {
        result_hash ^= shared_memory[i];
    }

    std::cout << "0x" << std::hex << std::setw(8) << std::setfill('0') << result_hash << std::endl;

    munmap(shared_memory, HASH_SIZE);
    close(shm_fd);
    shm_unlink("/hash_mem");

    return 0;
}