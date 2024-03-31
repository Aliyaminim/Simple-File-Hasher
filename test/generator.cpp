#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>
#include <string>
#include <stdexcept>

std::string generate_filename() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 1000);

    std::string filename = "test_";
    filename += std::to_string(dis(gen)) + ".bin";

    return filename;
}

void generate_binary_file(const std::string& filename, std::size_t size, double zero_ratio) {
    std::ofstream file(filename, std::ofstream::binary);
    if (!file.is_open())
        throw std::runtime_error ("ERROR: Can't open file " + filename);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution brnl_dist(zero_ratio);
    std::uniform_int_distribution<std::uint32_t> uint_dist;

    for(std::size_t i = 0; i < size; i++) {
        std::uint32_t value;
        if (brnl_dist(gen))
            value = 0;
        else
            value = uint_dist(gen);

        file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "ERROR: Incorrect input\nExpected: <filename> <size_in_elements_of_4bytes> <zero_elements_ratio>\n" << std::endl;
        return 1;
    }
    std::size_t file_size = std::stoul(argv[1]);
    double zero_ratio = std::stod(argv[2]);


    std::string directory = "test/";
    std::string filename = directory;
    filename += generate_filename();
    try {
        generate_binary_file(filename, file_size, zero_ratio);
        std::cout << filename << " is generated" << std::endl;
    }
    catch(const std::runtime_error& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}