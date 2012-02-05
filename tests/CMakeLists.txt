project(tfscr_tests)

include (GenerateTestFilesPaths)



find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


find_package(GMock REQUIRED)
include_directories(${GMOCK_INCLUDE_DIRS})




set(TestFileList
	test_data/test000000.c
)


generate_test_files_paths(TestFilePaths.h ${TestFileList})



set (TfscrTestsSources
	main.cpp

	VariablesVisitorTests.cpp
	TestFilePaths.h
)


set_source_files_properties (TestFilePaths.h PROPERTIES GENERATED 1)


add_executable(tfscr_tests ${TfscrTestsSources})

target_link_libraries(tfscr_tests
	${GTEST_LIBRARIES}
	${GMOCK_LIBRARIES}
	${LLVM_LFLAGS}
	${LLVM_LIBRARIES}
	${CLANG_LIBRARIES}
	libtfscr
)


add_test(
	NAME tfscr_tests
	COMMAND tfscr_tests
)
