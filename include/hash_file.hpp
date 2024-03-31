#pragma once

#include <cstdio>
#include <cstdint>
#include <string>

namespace file_hasher {

constexpr std::size_t BLOCK_SIZE = 0x100000;

std::uint32_t hash_file(const std::string& filename);

}