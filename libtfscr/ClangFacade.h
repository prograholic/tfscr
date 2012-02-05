#ifndef LIB_TFSCR_CLANG_FACADE_H
#define LIB_TFSCR_CLANG_FACADE_H

#include <boost/scoped_ptr.hpp>



#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>

#include <clang/AST/ASTContext.h>

#include <clang/Basic/LangOptions.h>
#include <clang/Basic/FileSystemOptions.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetOptions.h>

#include <clang/Frontend/CompilerInstance.h>



#include "CustomDiagnosticConsumer.h"
#include "VariablesVisitor.h"

namespace tfscr
{
	class ClangFacade
	{
	public:

		ClangFacade();

		~ClangFacade();

		void parseAST(const char * fileName, VariablesVisitor * visitor);

		clang::SourceManager & sourceManager();

	private:

		llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> mDiagnosticIDs;
		CustomDiagnosticConsumer mDiagnosticConsumer;
		boost::scoped_ptr<clang::DiagnosticsEngine> mDiagnosticsEngine;

		clang::LangOptions mLangOptions;
		clang::FileSystemOptions mFileSystemOptions;
		clang::FileManager mFileManager;
		boost::scoped_ptr<clang::SourceManager> mSourceManager;
		clang::HeaderSearch mHeaderSearch;

		clang::TargetOptions mTargetOptions;
		boost::scoped_ptr<clang::TargetInfo> mTargetInfo;

		clang::CompilerInstance mCompilerInstance;

		clang::IdentifierTable mIdentifierTable;
		clang::SelectorTable mSelectorTable;
		clang::Builtin::Context mBuiltinContext;





		boost::scoped_ptr<clang::Preprocessor> mPreprocessor;

		boost::scoped_ptr<clang::ASTContext> mASTContext;

	};
}



#endif /* LIB_TFSCR_CLANG_FACADE_H */
