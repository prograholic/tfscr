#include "ClangFacade.h"


#include <llvm/Support/Host.h>

#include <clang/Parse/ParseAST.h>
#include <clang/Basic/TargetInfo.h>

#include <clang/Basic/FileManager.h>
#include <clang/Basic/FileSystemOptions.h>

#include <clang/Lex/Preprocessor.h>


#include <clang/AST/ASTContext.h>


#include "CustomASTConsumer.h"
#include "CustomDiagnosticConsumer.h"

using namespace clang;


namespace tfscr
{

	ClangFacade::ClangFacade()
		: mCompiler(),
		  mLangOptions(),
		  mIdentifierTable(mLangOptions),
		  mSelectorTable(),
		  mBuiltinContext(),
		  mHeaderSearch()

	{
		mCompiler.setFileManager(new FileManager(FileSystemOptions()));

		llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> diagnosticIDs;
		std::auto_ptr<DiagnosticConsumer> consumer(new CustomDiagnosticConsumer);
		mCompiler.setDiagnostics(new DiagnosticsEngine(diagnosticIDs, consumer.get()));
		consumer.release();

		mCompiler.setSourceManager(new SourceManager(mCompiler.getDiagnostics(), mCompiler.getFileManager()));

		mTargetOptions.Triple = llvm::sys::getHostTriple();
		mCompiler.setTarget(TargetInfo::CreateTargetInfo(mCompiler.getDiagnostics(), mTargetOptions));

		mCompiler.setASTContext(new ASTContext(mLangOptions, mCompiler.getSourceManager(),
											   &mCompiler.getTarget(), mIdentifierTable,
											   mSelectorTable, mBuiltinContext, 0));


		mHeaderSearch.reset(new HeaderSearch(mCompiler.getFileManager()));
		mCompiler.setPreprocessor(new Preprocessor(mCompiler.getDiagnostics(), mLangOptions,
												   &mCompiler.getTarget(), mCompiler.getSourceManager(),
												   *mHeaderSearch, mCompiler));
	}


	CompilerInstance & ClangFacade::compiler()
	{
		return mCompiler;
	}


	bool ClangFacade::parseAST(const char * fileName, VariablesVisitor * visitor)
	{
		const FileEntry * fileEntry = mCompiler.getFileManager().getFile(fileName);
		mCompiler.getSourceManager().createMainFileID(fileEntry);

		CustomASTConsumer astConsumer(visitor);

		ParseAST(mCompiler.getPreprocessor(), &astConsumer, mCompiler.getASTContext());

		return !mCompiler.getDiagnostics().hasFatalErrorOccurred();
	}
}
