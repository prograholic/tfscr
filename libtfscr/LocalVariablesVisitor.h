#ifndef TFSCR_LOCAL_VARIABLES_VISITOR_H
#define TFSCR_LOCAL_VARIABLES_VISITOR_H


#include <clang/AST/StmtVisitor.h>

#include <list>

namespace tfscr
{
	typedef std::list<clang::VarDecl *> VarDeclList;


	typedef std::list<clang::SourceRange> SourceRangeList;

	class LocalVariablesVisitor: public clang::StmtVisitor<LocalVariablesVisitor>
	{
	public:

		void VisitDeclRefExpr(clang::DeclRefExpr * expr);

		void VisitStmt(clang::Stmt* stmt);

		void VisitBinAssign(clang::BinaryOperator * S);

		void process(clang::FunctionDecl * fd);


		VarDeclList varList();

		SourceRangeList assignLocations();


	private:

		VarDeclList mVarsList;

		SourceRangeList mAssignLocations;



	};
}


#endif /* TFSCR_LOCAL_VARIABLES_VISITOR_H */
