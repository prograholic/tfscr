#include "CustomDiagnosticConsumer.h"

#include <iostream>

#include <llvm/ADT/SmallString.h>
#include <clang/Basic/SourceManager.h>


using namespace clang;
using namespace llvm;

namespace tfscr
{

	CustomDiagnosticConsumer::CustomDiagnosticConsumer(TfscrDiagnosticListener * listener)
		: DiagnosticConsumer(), mListener(listener)
	{

	}

	void CustomDiagnosticConsumer::setListener(TfscrDiagnosticListener * listener)
	{
		mListener = listener;
	}

	void CustomDiagnosticConsumer::HandleDiagnostic(DiagnosticsEngine::Level diagLevel, const Diagnostic & info)
	{
		if (mListener)
		{
			SmallString<1000> msg;
			info.FormatDiagnostic(msg);

			DiagnosticInfo result;
			result.message = msg.c_str();

			SourceLocation l = info.getLocation();
			SourceManager & srcMgr  = info.getSourceManager();
			PresumedLoc pLoc = srcMgr.getPresumedLoc(l);

			result.fileName = pLoc.getFilename();
			result.line = pLoc.getLine();
			result.column = pLoc.getColumn();

			mListener->onDiagnostic(result);
		}
	}

	CustomDiagnosticConsumer * CustomDiagnosticConsumer::clone(DiagnosticsEngine & Diags) const
	{
		return new CustomDiagnosticConsumer();
	}
}
