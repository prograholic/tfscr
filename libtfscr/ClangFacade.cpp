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


	void ClangFacade::parseAST(const char * fileName)
	{
		const FileEntry * fileEntry = mFileManager.getFile(fileName);
		mSourceManager->createMainFileID(fileEntry);


		CustomASTConsumer astConsumer;

		ParseAST(*mPreprocessor, &astConsumer, *mASTContext);

		mVarDeclList = astConsumer.varList();
	}


	const char * ClangFacade::fileName() const
	{
		FileID fileId = mSourceManager->getMainFileID();
		const FileEntry * fileEntry = mSourceManager->getFileEntryForID(fileId);

		return fileEntry->getName();
	}

	VarDeclList ClangFacade::varList() const
	{
		return mVarDeclList;
	}


	SourceManager & ClangFacade::sourceManager()
	{
		return *mSourceManager;
	}
}
