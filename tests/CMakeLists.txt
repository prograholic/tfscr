project(tfscr_test)

set (TfscrTestSources
	main.cpp
)


include_directories(${TFSCR_ROOT_SOURCE_DIR}/libtfscr)


add_executable(tfscr_test ${TfscrTestSources})

target_link_libraries(tfscr_test
	${LLVM_LFLAGS}
	${LLVM_LIBRARIES}
	${CLANG_LIBRARIES}
	libtfscr
)
