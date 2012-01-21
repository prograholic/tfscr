cmake_minimum_required(VERSION 2.8)

project (tfscr)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


find_package(LLVM 3.0 REQUIRED)
find_package(CLANG 3.0 REQUIRED)


include_directories(${LLVM_INCLUDE_DIR})
add_definitions(${LLVM_DEFINITIONS})

include_directories(${CLANG_INCLUDE_DIR})
add_definitions(${CLANG_DEFINITIONS})



add_subdirectory(src)
add_subdirectory(include)


enable_testing()
add_subdirectory(tests)
