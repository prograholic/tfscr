#ifndef LIB_TFSCR_CLANG_FACADE_H
#define LIB_TFSCR_CLANG_FACADE_H

#include <boost/scoped_ptr.hpp>




#include <clang/Lex/HeaderSearch.h>
#include <clang/Basic/LangOptions.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Basic/Builtins.h>
#include <clang/Frontend/CompilerInstance.h>


#include "VariablesVisitor.h"

namespace tfscr
{
	class ClangFacade
	{
	public:
		ClangFacade();

		bool parseAST(const char * fileName, VariablesVisitor * visitor);

		clang::CompilerInstance & compiler();

	private:

		clang::CompilerInstance mCompiler;

		clang::LangOptions mLangOptions;
		clang::IdentifierTable mIdentifierTable;
		clang::SelectorTable mSelectorTable;
		clang::Builtin::Context mBuiltinContext;
		clang::TargetOptions mTargetOptions;
		boost::scoped_ptr<clang::HeaderSearch> mHeaderSearch;
	};
}



#endif /* LIB_TFSCR_CLANG_FACADE_H */
