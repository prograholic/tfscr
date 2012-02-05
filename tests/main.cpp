#include "ClangFacade.h"


struct TestVariablesVisitor: public tfscr::VariablesVisitor
{
	virtual void onFunctionParam(clang::ParmVarDecl * param)
	{

	}

	virtual void onVariableDeclaration(clang::VarDecl * varDecl)
	{

	}

	virtual void onArraySubscriptExpr(clang::ArraySubscriptExpr * arraySubscriptExpr)
	{

	}


};



int main(int argc, char * argv [])
{

	if (argc != 2)
	{
		return 1;
	}

	tfscr::ClangFacade clangFacade;
	TestVariablesVisitor visitor;

	clangFacade.parseAST(argv[1], &visitor);

	return 0;
}
