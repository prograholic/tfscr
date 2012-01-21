# - Find clang libraries and headers
# Find the native clang includes and library
#
#  CLANG_INCLUDE_DIR - where to find include
#  CLANG_DEFINITIONS - compiler definitions
#  CLANG_LIBRARIES   - List of libraries
#  CLANG_FOUND       - True if clang found.


message(WARNING "FindCLANG is not fully implemented")


if (NOT LLVM_FOUND)
	message(FATAL_ERROR "clang required llvm package")
endif()



set(CLANG_INCLUDE_DIR ${LLVM_INCLUDE_DIR})


set(CLANG_DEFINITIONS -fno-rtti)

set(CLANG_LIBRARIES
	clangFrontend
	clangParse
	clangSema
	clangAnalysis
	clangAST
	clangLex
	clangBasic
	clangDriver
	clangSerialization

	LLVMMC
	LLVMSupport
)


set (CLANG_FOUND YES)
