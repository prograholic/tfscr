project(tfscr_ui)





set(TfScrUiSources
	main.cpp
	MainWindow.cpp
)


set (TfScrUiHeaders
	MainWindow.h
)



QT4_WRAP_CPP(QT4_MOC_GENERATED_SOURCES ${TfScrUiHeaders})
QT4_WRAP_UI(QT4_UI_GENERATED_SOURCE MainWindow.ui)


include_directories(${CMAKE_CURRENT_BINARY_DIR})



add_executable(tfscr_ui
	${TfScrUiSources}
	${TfScrUiHeaders}

	${QT4_MOC_GENERATED_SOURCES}
	${QT4_UI_GENERATED_SOURCE}
)




target_link_libraries(tfscr_ui
	${LLVM_LFLAGS}
	${LLVM_LIBRARIES}
	${CLANG_LIBRARIES}
	libtfscr
	${QT_LIBRARIES}
)
