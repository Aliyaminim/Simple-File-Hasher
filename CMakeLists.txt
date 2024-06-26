cmake_minimum_required(VERSION 3.13)

project(File_hasher)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR})
    message(FATAL_ERROR "In-source build is forbidden")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -Wall -fsanitize=address")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(driver ./src/main.cpp ./src/process.cpp ./src/hash_file.cpp)
target_include_directories(driver PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(driver_multi ./src/main_multi.cpp ./src/process.cpp ./src/hash_file.cpp)
target_include_directories(driver_multi PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(test)
#cmake -DCMAKE_BUILD_TYPE=Debug