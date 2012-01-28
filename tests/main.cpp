#include "ClangFacade.h"

int main(int argc, char * argv [])
{

	if (argc != 2)
	{
		return 1;
	}

	tfscr::ClangFacade clangFacade;

	clangFacade.parseAST(argv[1]);

	return 0;
}
