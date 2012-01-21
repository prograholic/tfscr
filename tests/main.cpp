#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"

#include "clang/Frontend/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"

#include "clang/Basic/LangOptions.h"
#include "clang/Basic/FileSystemOptions.h"

#include "clang/Basic/SourceManager.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Basic/FileManager.h"

#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"

#include "clang/Lex/Preprocessor.h"
#include "clang/Frontend/CompilerInstance.h"

#include "clang/Parse/ParseAST.h"
#include "clang/Parse/Parser.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Frontend/CompilerInstance.h"



#include <iostream>


#include "CustomASTConsumer.h"


int main(int argc, char * argv [])
{

    if (argc != 2)
    {
        return 1;
    }


    clang::DiagnosticOptions diagnosticOptions;
    clang::TextDiagnosticPrinter *pTextDiagnosticPrinter =
        new clang::TextDiagnosticPrinter(
            llvm::nulls(),
            diagnosticOptions);
    llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> pDiagIDs;

    clang::DiagnosticsEngine *pDiagnosticsEngine =
        new clang::DiagnosticsEngine(pDiagIDs, pTextDiagnosticPrinter);

    clang::LangOptions languageOptions;
    clang::FileSystemOptions fileSystemOptions;
    clang::FileManager fileManager(fileSystemOptions);
    clang::SourceManager sourceManager(
        *pDiagnosticsEngine,
        fileManager);
    clang::HeaderSearch headerSearch(fileManager);

    clang::TargetOptions targetOptions;
    targetOptions.Triple = llvm::sys::getHostTriple();

    clang::TargetInfo *pTargetInfo =
        clang::TargetInfo::CreateTargetInfo(
            *pDiagnosticsEngine,
            targetOptions);
    clang::CompilerInstance compInst;

    clang::Preprocessor preprocessor(
        *pDiagnosticsEngine,
        languageOptions,
        pTargetInfo,
        sourceManager,
        headerSearch,
        compInst);


    const clang::TargetInfo & targetInfo = *pTargetInfo;

    clang::IdentifierTable identifierTable(languageOptions);
    clang::SelectorTable selectorTable;

    clang::Builtin::Context builtinContext;
    builtinContext.InitializeTarget(targetInfo);
    clang::ASTContext astContext(
                languageOptions,
                sourceManager,
                pTargetInfo,
                identifierTable,
                selectorTable,
                builtinContext,
                0 /* size_reserve*/);

    CustomASTConsumer astConsumer;

    clang::Sema sema(
                preprocessor,
                astContext,
                astConsumer);


    const clang::FileEntry * file = fileManager.getFile(argv[1]);
    sourceManager.createMainFileID(file);
    pTextDiagnosticPrinter->BeginSourceFile(languageOptions, &preprocessor);
    clang::ParseAST(preprocessor, &astConsumer, astContext);
    pTextDiagnosticPrinter->EndSourceFile();
    //identifierTable.PrintStats();

    return 0;
}
