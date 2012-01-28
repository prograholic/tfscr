#ifndef CUSTOMASTCONSUMER_H
#define CUSTOMASTCONSUMER_H

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Decl.h>



#include "CommonTypes.h"

namespace tfscr
{
	class CustomASTConsumer : public clang::ASTConsumer
	{
	public:
		CustomASTConsumer();

		virtual ~CustomASTConsumer();

		virtual void Initialize(clang::ASTContext & Context);

		virtual void HandleTopLevelDecl(clang::DeclGroupRef D);

		virtual void HandleInterestingDecl(clang::DeclGroupRef D);

		virtual void HandleTranslationUnit(clang::ASTContext & Ctx);

		virtual void HandleTagDeclDefinition(clang::TagDecl *D);

		virtual void CompleteTentativeDefinition(clang::VarDecl *D);

		virtual void HandleVTable(clang::CXXRecordDecl *RD, bool DefinitionRequired);

		virtual clang::ASTMutationListener * GetASTMutationListener();

		virtual clang::ASTDeserializationListener * GetASTDeserializationListener();

		virtual void PrintStats();

		VarDeclList varList() const;

		SourceRangeList assignLocations() const;


	private:
		typedef std::list<clang::FunctionDecl *> FunctionDeclList;
		FunctionDeclList mFunctions;

		VarDeclList mVarsList;
		SourceRangeList mAssignLocations;

	};

}


#endif // CUSTOMASTCONSUMER_H
