#ifndef LIB_TFSCR_TESTS_MOCK_VARIABLES_VISITOR_H
#define LIB_TFSCR_TESTS_MOCK_VARIABLES_VISITOR_H

#include <gmock/gmock.h>

#include "VariablesVisitor.h"

namespace mocks
{
	class MockVariablesVisitor: public tfscr::VariablesVisitor
	{
	public:

		MOCK_METHOD1(onFunctionParam, void (clang::ParmVarDecl * param));

		MOCK_METHOD1(onVariableDeclaration, void (clang::VarDecl * varDecl));

		MOCK_METHOD1(onLhsInBinaryAssignment, void (clang::Expr * lhs));

	};
}


#endif /* LIB_TFSCR_TESTS_MOCK_VARIABLES_VISITOR_H */
