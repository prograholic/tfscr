MACRO (generate_test_files_paths result_file file_list)


foreach (it ${file_list})

	FILE(WRITE ${result_file} "#ifndef GENERATED_TEST_FILES_PATH_H\n")
	FILE(APPEND ${result_file} "#define GENERATED_TEST_FILES_PATH_H\n\n\n")

	FILE(APPEND ${result_file} "/* WARNING this file is automatically generated with CMake, do not edit */\n\n")

	unset(full_test_file_name)
	find_file(full_test_file_name ${it} ${CMAKE_CURRENT_SOURCE_DIR})
	if (NOT full_test_file_name)
		message(FATAL_ERROR "cannot find [${it}] in ${CMAKE_CURRENT_SOURCE_DIR} ...")
	else()
		get_filename_component(var_name ${full_test_file_name} NAME_WE)

		STRING(CONFIGURE ${full_test_file_name} full_test_file_name ESCAPE_QUOTES)
		FILE(APPEND ${result_file} "const char ${var_name} [] = \"${full_test_file_name}\";\n")

		message(STATUS "added file: ${full_test_file_name} to testsuite with name: [${var_name}]")
	endif()


	FILE(APPEND ${result_file} "\n\n#endif /* GENERATED_TEST_FILES_PATH_H */\n")


endforeach()

ENDMACRO(generate_test_files_paths)