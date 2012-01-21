#include "CustomASTConsumer.h"



#include "clang/Frontend/ASTConsumers.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/FileManager.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/PrettyPrinter.h"
#include "llvm/Module.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Path.h"

#include <clang/AST/StmtVisitor.h>

using namespace clang;




class LocalVariablesVisitor: public StmtVisitor<LocalVariablesVisitor>
{
public:
    void VisitDeclRefExpr(DeclRefExpr * expr)
    {
        if (VarDecl * vd = dyn_cast<VarDecl>(expr->getDecl()))
        {
            llvm::outs() << "variable declaration: " << vd->getName() << "\n";
        }
        else
        {
            llvm::outs() << "other expr: " << expr->getDecl()->getName() << "\n";
        }
    }

    void VisitStmt(Stmt* stmt)
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

    void VisitBinAssign(BinaryOperator * S)
    {
        llvm::outs() << "\n\n";
        S->dump();
        llvm::outs() << "\n\n";
        llvm::outs() << "assignment founded: " << S->getStmtClassName() << "\n";
        if (Expr * lhs = S->getLHS())
        {
            if (ArraySubscriptExpr * arrSubscript = dyn_cast<ArraySubscriptExpr>(lhs))
            {
                llvm::outs() << "array subscript as lhs\n";
            }
            else
            {
                llvm::outs() << "  lhs: " << lhs->getStmtClassName() << "\n";
            }
        }
        if (Expr * rhs = S->getRHS())
        {
            llvm::outs() << "  rhs: " << rhs->getStmtClassName() << "\n";
        }
    }


    void VisitBinAddAssign(CompoundAssignOperator * S)
    {

    }


    void process(FunctionDecl * fd)
    {
        Visit(fd->getBody());
    }
};




CustomASTConsumer::CustomASTConsumer(): clang::ASTConsumer()
{
}

CustomASTConsumer::~CustomASTConsumer()
{
}

void CustomASTConsumer::Initialize(ASTContext & Context)
{
}

void CustomASTConsumer::HandleTopLevelDecl(DeclGroupRef D)
{
    ASTConsumer::HandleTopLevelDecl(D);

    for (DeclGroupRef::iterator it = D.begin(); it != D.end(); ++it)
    {
        Decl * decl = *it;
        if (FunctionDecl * funcDecl = dyn_cast<FunctionDecl>(decl))
        {
            mFunctions.push_back(funcDecl);
        }
    }
}

void CustomASTConsumer::HandleInterestingDecl(clang::DeclGroupRef D)
{
    ASTConsumer::HandleInterestingDecl(D);
}

void CustomASTConsumer::HandleTranslationUnit(clang::ASTContext & Ctx)
{
    LocalVariablesVisitor visitor;
    for (FunctionDeclList::iterator it = mFunctions.begin(); it != mFunctions.end(); ++it)
    {
        visitor.process(*it);
    }
}

void CustomASTConsumer::HandleTagDeclDefinition(clang::TagDecl *D)
{
}

void CustomASTConsumer::CompleteTentativeDefinition(clang::VarDecl *D)
{
}

void CustomASTConsumer::HandleVTable(clang::CXXRecordDecl *RD, bool DefinitionRequired)
{
}

clang::ASTMutationListener * CustomASTConsumer::GetASTMutationListener()
{
    return 0;
}

clang::ASTDeserializationListener * CustomASTConsumer::GetASTDeserializationListener()
{
    return 0;
}

void CustomASTConsumer::PrintStats()
{
    ASTConsumer::PrintStats();
}
