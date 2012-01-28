#ifndef LIB_TFSCR_COMMON_TYPES_H
#define LIB_TFSCR_COMMON_TYPES_H

#include <clang/Basic/SourceLocation.h>
#include <clang/AST/Decl.h>


#include <list>

namespace tfscr
{
	typedef std::list<clang::VarDecl *> VarDeclList;


	typedef std::list<clang::SourceRange> SourceRangeList;
}


#endif /* LIB_TFSCR_COMMON_TYPES_H */
