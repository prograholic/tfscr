#include "CustomASTConsumer.h"



#include "clang/Frontend/ASTConsumers.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/FileManager.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/PrettyPrinter.h"
#include "llvm/Module.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Path.h"

#include <clang/AST/StmtVisitor.h>



#include "LocalVariablesVisitor.h"


using namespace clang;



namespace tfscr
{
	CustomASTConsumer::CustomASTConsumer()
		: clang::ASTConsumer()
	{
	}

	CustomASTConsumer::~CustomASTConsumer()
	{
	}

	void CustomASTConsumer::Initialize(ASTContext & Context)
	{
	}

	void CustomASTConsumer::HandleTopLevelDecl(DeclGroupRef D)
	{
		ASTConsumer::HandleTopLevelDecl(D);

		for (DeclGroupRef::iterator it = D.begin(); it != D.end(); ++it)
		{
			Decl * decl = *it;
			if (FunctionDecl * funcDecl = dyn_cast<FunctionDecl>(decl))
			{
				mFunctions.push_back(funcDecl);
			}
		}
	}

	void CustomASTConsumer::HandleInterestingDecl(clang::DeclGroupRef D)
	{
		ASTConsumer::HandleInterestingDecl(D);
	}

	void CustomASTConsumer::HandleTranslationUnit(clang::ASTContext & Ctx)
	{
		LocalVariablesVisitor visitor;
		for (FunctionDeclList::iterator it = mFunctions.begin(); it != mFunctions.end(); ++it)
		{
			visitor.process(*it);
		}
	}

	void CustomASTConsumer::HandleTagDeclDefinition(clang::TagDecl *D)
	{
	}

	void CustomASTConsumer::CompleteTentativeDefinition(clang::VarDecl *D)
	{
	}

	void CustomASTConsumer::HandleVTable(clang::CXXRecordDecl *RD, bool DefinitionRequired)
	{
	}

	clang::ASTMutationListener * CustomASTConsumer::GetASTMutationListener()
	{
		return 0;
	}

	clang::ASTDeserializationListener * CustomASTConsumer::GetASTDeserializationListener()
	{
		return 0;
	}

	void CustomASTConsumer::PrintStats()
	{
		ASTConsumer::PrintStats();
	}
}





