project(tfscr_test)

set (TfscrTestSources
	main.cpp
)


add_executable(tfscr_test ${TfscrTestSources})

target_link_libraries(tfscr_test
	${LLVM_LFLAGS}
	${LLVM_LIBRARIES}
	${CLANG_LIBRARIES}
	libtfscr
)
