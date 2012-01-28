#ifndef TFSCR_LOCAL_VARIABLES_VISITOR_H
#define TFSCR_LOCAL_VARIABLES_VISITOR_H


#include <clang/AST/StmtVisitor.h>
#include "CommonTypes.h"

namespace tfscr
{


	class LocalVariablesVisitor: public clang::StmtVisitor<LocalVariablesVisitor>
	{
	public:

		void VisitDeclRefExpr(clang::DeclRefExpr * expr);

		void VisitStmt(clang::Stmt * stmt);

		void VisitBinAssign(clang::BinaryOperator * S);

		void process(clang::FunctionDecl * fd);


		VarDeclList varList() const;

		SourceRangeList assignLocations() const;


	private:

		VarDeclList mVarsList;

		SourceRangeList mAssignLocations;



	};
}


#endif /* TFSCR_LOCAL_VARIABLES_VISITOR_H */
