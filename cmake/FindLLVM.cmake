# - Find llvm libraries and headers
# Find the native LLVM includes and library
#
#  LLVM_INCLUDE_DIR - where to find include
#  LLVM_DEFINITIONS - compiler definitions
#  LLVM_LIBRARIES   - List of libraries
#  LLVM_FOUND       - True if llvm found.



message(WARNING "FindLLVM is not fully implemented")

find_program(LLVM_CONFIG_EXECUTABLE NAMES llvm-config DOC "llvm-config executable")

if (LLVM_CONFIG_EXECUTABLE)
	message(STATUS "llvm-config founded: ${LLVM_CONFIG_EXECUTABLE}")
else()
	message(FATAL_ERROR "llvm-config cannot be founded")
endif()

if (LLVM_FIND_VERSION)
	message(STATUS "finding llvm libraries for version ${LLVM_FIND_VERSION}...")

	execute_process(
		COMMAND ${LLVM_CONFIG_EXECUTABLE} --version
		OUTPUT_VARIABLE LLVM_CONFIG_VERSION
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)

	if (${LLVM_FIND_VERSION} STREQUAL ${LLVM_CONFIG_VERSION})
	else()
		message(FATAL_ERROR "wrong version of llvm: ${LLVM_CONFIG_VERSION}, expected: ${LLVM_FIND_VERSION}")
	endif()
	
endif()


execute_process(
	COMMAND ${LLVM_CONFIG_EXECUTABLE} --includedir
	OUTPUT_VARIABLE LLVM_INCLUDE_DIR
	OUTPUT_STRIP_TRAILING_WHITESPACE
)


execute_process(
        COMMAND ${LLVM_CONFIG_EXECUTABLE} --cppflags
	OUTPUT_VARIABLE LLVM_DEFINITIONS
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
	COMMAND ${LLVM_CONFIG_EXECUTABLE} --ldflags
	OUTPUT_VARIABLE LLVM_LFLAGS
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND ${LLVM_CONFIG_EXECUTABLE} --libs core jit native linker bitreader bitwriter ipo
	OUTPUT_VARIABLE LLVM_JIT_LIBS
	OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
	COMMAND ${LLVM_CONFIG_EXECUTABLE} --libs all
        OUTPUT_VARIABLE LLVM_LIBRARIES
	OUTPUT_STRIP_TRAILING_WHITESPACE
)


set (LLVM_FOUND YES)
#message("llvm jit libs: " ${LLVM_JIT_LIBS})
#message("llvm all libs: " ${LLVM_LIBRARIES})
#message("llvm definitions: " ${LLVM_DEFINITIONS})

