#pragma once

#include <vector>
#include <cstdint>

namespace file_hasher {

class data_processor_t final {
    std::uint32_t m_last_hash = 0;
public:
    std::uint32_t process_block( const std::vector<std::uint32_t> &block );
};

}