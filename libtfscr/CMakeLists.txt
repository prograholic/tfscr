project (libtfscr)




set (LibTfscrSources
	ClangFacade.cpp
	ClangFacade.h
	CustomASTConsumer.cpp
	CustomASTConsumer.h
	LocalVariablesVisitor.cpp
	LocalVariablesVisitor.h
	CustomDiagnosticConsumer.cpp
	CustomDiagnosticConsumer.h
	CommonTypes.h
)





add_library(libtfscr STATIC ${LibTfscrSources})

target_link_libraries(libtfscr
	${LLVM_LFLAGS}
	${LLVM_LIBRARIES}
	${CLANG_LIBRARIES}
)





#todo add `install` target
