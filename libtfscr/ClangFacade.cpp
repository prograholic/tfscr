#include "ClangFacade.h"

#include <clang/Parse/ParseAST.h>
#include <clang/Basic/TargetInfo.h>

#include <llvm/Support/Host.h>

#include "CustomASTConsumer.h"

using namespace clang;


namespace tfscr
{


	ClangFacade::ClangFacade():
		mDiagnosticIDs(),
		mDiagnosticConsumer(),
		mDiagnosticsEngine(new DiagnosticsEngine(mDiagnosticIDs, &mDiagnosticConsumer, false)),

		mLangOptions(),
		mFileSystemOptions(),
		mFileManager(mFileSystemOptions),
		mSourceManager(),
		mHeaderSearch(mFileManager),

		mTargetOptions(),
		mTargetInfo(),

		mCompilerInstance(),

		mIdentifierTable(mLangOptions),
		mSelectorTable(),
		mBuiltinContext()
	{
		mSourceManager.reset(new SourceManager(*mDiagnosticsEngine, mFileManager));

		mTargetOptions.Triple = llvm::sys::getHostTriple();
		mTargetInfo.reset(TargetInfo::CreateTargetInfo(*mDiagnosticsEngine, mTargetOptions));

		mPreprocessor.reset(new Preprocessor(
								*mDiagnosticsEngine,
								mLangOptions,
								mTargetInfo.get(),
								*mSourceManager,
								mHeaderSearch,
								mCompilerInstance));


		mBuiltinContext.InitializeTarget(*mTargetInfo);

		mASTContext.reset(new ASTContext(
			mLangOptions,
			*mSourceManager,
			mTargetInfo.get(),
			mIdentifierTable,
			mSelectorTable,
			mBuiltinContext,
			0));
	}

	ClangFacade::~ClangFacade()
	{

	}

	void ClangFacade::parseAST(const char * fileName, VariablesVisitor *visitor)
	{
		const FileEntry * fileEntry = mFileManager.getFile(fileName);
		mSourceManager->createMainFileID(fileEntry);


		CustomASTConsumer astConsumer(visitor);

		ParseAST(*mPreprocessor, &astConsumer, *mASTContext);
	}


	SourceManager & ClangFacade::sourceManager()
	{
		return *mSourceManager;
	}
}
