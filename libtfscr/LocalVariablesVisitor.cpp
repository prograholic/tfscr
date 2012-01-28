#include "LocalVariablesVisitor.h"


using namespace clang;


namespace tfscr
{
	void LocalVariablesVisitor::VisitDeclRefExpr(DeclRefExpr * expr)
	{
		if (VarDecl * vd = dyn_cast<VarDecl>(expr->getDecl()))
		{
			mVarsList.push_back(vd);
		}
		else
		{

			llvm::outs() << "other expr: " << expr->getDecl()->getName() << "\n";
		}
	}

	void LocalVariablesVisitor::VisitStmt(Stmt* stmt)
	{
		Stmt::child_iterator CI, CE = stmt->child_end();
		for (CI = stmt->child_begin(); CI != CE; ++CI)
		{
			if (*CI != 0)
			{
				Visit(*CI);
			}
		}
	}

	void LocalVariablesVisitor::VisitBinAssign(BinaryOperator * S)
	{
		if (Expr * lhs = S->getLHS())
		{
			SourceRange loc = lhs->getSourceRange();
			mAssignLocations.push_back(loc);

			Visit(lhs);

			/*
			if (ArraySubscriptExpr * arrSubscript = dyn_cast<ArraySubscriptExpr>(lhs))
			{
				llvm::outs() << "array subscript as lhs\n";
			}
			else
			{
				llvm::outs() << "  lhs: " << lhs->getStmtClassName() << "\n";
			}
			*/
		}
		if (Expr * rhs = S->getRHS())
		{
			Visit(rhs);
			//llvm::outs() << "  rhs: " << rhs->getStmtClassName() << "\n";
		}
	}

	void LocalVariablesVisitor::process(FunctionDecl * fd)
	{
		for (FunctionDecl::param_const_iterator it = fd->param_begin(); it != fd->param_end(); ++it)
		{
			ParmVarDecl * param = *it;
			mVarsList.push_back(param);
			//llvm::outs() << "param: ";
			//param->print(llvm::outs());
			//llvm::outs() << "\n";
		}
		Visit(fd->getBody());
	}


	VarDeclList LocalVariablesVisitor::varList() const
	{
		return mVarsList;
	}

	SourceRangeList LocalVariablesVisitor::assignLocations() const
	{
		return mAssignLocations;
	}
}



