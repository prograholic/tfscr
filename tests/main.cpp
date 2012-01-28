
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"

#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/Basic/LangOptions.h"
#include "clang/Basic/FileSystemOptions.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Basic/FileManager.h"

#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"

#include "clang/Lex/Preprocessor.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/Parse/ParseAST.h"
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"



#include <iostream>


#include "CustomASTConsumer.h"




#include "ClangFacade.h"

int main(int argc, char * argv [])
{

	if (argc != 2)
	{
		return 1;
	}

	tfscr::ClangFacade clangFacade;

	clangFacade.parseAST(argv[1]);

	return 0;
}
