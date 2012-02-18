#include "VariablesVisitor.h"


using namespace clang;


namespace tfscr
{
	bool VariablesVisitor::VisitDecl(Decl * d)
	{
		if (FunctionDecl * funcDecl = dyn_cast<FunctionDecl>(d))
		{
			for (FunctionDecl::param_const_iterator it = funcDecl->param_begin(); it != funcDecl->param_end(); ++it)
			{
				ParmVarDecl * param = *it;
				this->onFunctionParam(param);
			}
			return true;
		}

		if (VarDecl * vd = dyn_cast<VarDecl>(d))
		{
			this->onVariableDeclaration(vd);
			return true;
		}

		return true;
	}

	bool VariablesVisitor::VisitBinAssign(BinaryOperator * S)
	{
		if (Expr * lhs = S->getLHS())
		{
			if (ArraySubscriptExpr * arrSubscript = dyn_cast<ArraySubscriptExpr>(lhs))
			{
				this->onLhsInBinaryAssignment(arrSubscript);
				return true;
			}
			if (CXXOperatorCallExpr * operatorCall = dyn_cast<CXXOperatorCallExpr>(lhs))
			{
				if (operatorCall->getOperator() == OO_Subscript)
				{
					this->onLhsInBinaryAssignment(lhs);
					return true;
				}
			}
		}
		if (Expr * rhs = S->getRHS())
		{
			//Visit(rhs);
			//llvm::outs() << "  rhs: " << rhs->getStmtClassName() << "\n";
		}

		return true;
	}
}
