#include <gtest/gtest.h>

#include "ClangFacade.h"
#include "mocks/MockVariablesVisitor.h"

#include "TestFilePaths.h"


using namespace clang;
using namespace tfscr;

using ::testing::AnyNumber;
using ::testing::Invoke;


class VariablesVisitorTest: public ::testing::Test
{
public:

	virtual void SetUp()
	{

	}


	virtual void TearDown()
	{

	}


	ClangFacade clangFacade;
};



TEST_F(VariablesVisitorTest, CheckFileTest000000)
{
	mocks::MockVariablesVisitor visitor;

	clangFacade.parseAST(test000000, &visitor);
}
