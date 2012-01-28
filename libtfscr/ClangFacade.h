#ifndef LIB_TFSCR_CLANG_FACADE_H
#define LIB_TFSCR_CLANG_FACADE_H

#include "CustomDiagnosticConsumer.h"

#include <clang/Lex/Preprocessor.h>
#include <clang/Lex/HeaderSearch.h>

#include <clang/AST/ASTContext.h>

#include <clang/Basic/LangOptions.h>
#include <clang/Basic/FileSystemOptions.h>
#include <clang/Basic/FileManager.h>
#include <clang/Basic/TargetOptions.h>

#include <clang/Frontend/CompilerInstance.h>

#include <boost/scoped_ptr.hpp>

namespace tfscr
{
	class ClangFacade
	{
	public:

		ClangFacade();


		void parseAST(const std::string & fileName);


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
