#ifndef LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H
#define LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H

#include <clang/Basic/Diagnostic.h>


namespace tfscr
{
	class CustomDiagnosticConsumer: public clang::DiagnosticConsumer
	{
	public:

		CustomDiagnosticConsumer();


		virtual CustomDiagnosticConsumer * clone(clang::DiagnosticsEngine & Diags) const;

	};
}

#endif /* LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H */
