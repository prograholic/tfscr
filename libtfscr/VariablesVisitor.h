#ifndef TFSCR_VARIABLES_VISITOR_H
#define TFSCR_VARIABLES_VISITOR_H

#include <clang/AST/RecursiveASTVisitor.h>

namespace tfscr
{


	class VariablesVisitor: public clang::RecursiveASTVisitor<VariablesVisitor>
	{
	public:

		bool VisitDecl(clang::Decl * d);

		bool VisitBinAssign(clang::BinaryOperator * S);

	private:


		virtual void onFunctionParam(clang::ParmVarDecl * param) = 0;

		virtual void onVariableDeclaration(clang::VarDecl * varDecl) = 0;

		virtual void onArraySubscriptExpr(clang::ArraySubscriptExpr * arraySubscriptExpr) = 0;


	};
}


#endif /* TFSCR_LOCAL_VARIABLES_VISITOR_H */
