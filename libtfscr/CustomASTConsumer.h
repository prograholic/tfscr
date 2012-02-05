#ifndef CUSTOMASTCONSUMER_H
#define CUSTOMASTCONSUMER_H

#include <clang/AST/ASTConsumer.h>

#include "VariablesVisitor.h"


namespace tfscr
{
	class CustomASTConsumer : public clang::ASTConsumer
	{
	public:
		CustomASTConsumer(VariablesVisitor * visitor);

		virtual ~CustomASTConsumer();

		virtual void Initialize(clang::ASTContext & Context);

		virtual void HandleTopLevelDecl(clang::DeclGroupRef D);

		virtual void HandleTranslationUnit(clang::ASTContext & Ctx);


	private:

		VariablesVisitor * mVisitor;

	};

}


#endif // CUSTOMASTCONSUMER_H
