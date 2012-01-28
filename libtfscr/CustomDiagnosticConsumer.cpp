#include "CustomDiagnosticConsumer.h"


using namespace clang;

namespace tfscr
{

	CustomDiagnosticConsumer::CustomDiagnosticConsumer()
		: DiagnosticConsumer()
	{

	}

	CustomDiagnosticConsumer * CustomDiagnosticConsumer::clone(DiagnosticsEngine & Diags) const
	{
		return new CustomDiagnosticConsumer();
	}
}
