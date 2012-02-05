#include "CustomASTConsumer.h"


using namespace clang;

namespace tfscr
{

	CustomASTConsumer::CustomASTConsumer(VariablesVisitor * visitor)
		: ASTConsumer(), mVisitor(visitor)
	{
	}

	CustomASTConsumer::~CustomASTConsumer()
	{
	}

	void CustomASTConsumer::Initialize(ASTContext & /* Context */)
	{
	}


	void CustomASTConsumer::HandleTopLevelDecl(DeclGroupRef D)
	{
		for (DeclGroupRef::iterator it = D.begin(); it != D.end(); ++it)
		{
			Decl * decl = *it;
			mVisitor->TraverseDecl(decl);
		}

	}


	void CustomASTConsumer::HandleTranslationUnit(clang::ASTContext & Ctx)
	{
		/// maybe later...
	}
}





