cmake_minimum_required(VERSION 2.8)

project (tfscr)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)



set(TFSCR_ROOT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})


find_package(LLVM 3.0 REQUIRED)
include_directories(${LLVM_INCLUDE_DIR})
add_definitions(${LLVM_DEFINITIONS})


find_package(CLANG 3.0 REQUIRED)
include_directories(${CLANG_INCLUDE_DIR})
add_definitions(${CLANG_DEFINITIONS})


find_package(Boost REQUIRED)
include_directories(${BOOST_INCLUDE_DIR})
add_definitions(${BOOST_DEFINITIONS})



add_subdirectory(libtfscr)
include_directories(libtfscr)


find_package(Qt4 COMPONENTS QtCore QtGui)
if (QT4_FOUND)
	include(${QT_USE_FILE})

	add_subdirectory(ui)
endif()




enable_testing()
add_subdirectory(tests)
