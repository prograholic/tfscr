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
)





add_library(libtfscr STATIC ${LibTfscrSources})






#todo add `install` target
