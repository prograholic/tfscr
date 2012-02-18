#ifndef LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H
#define LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H

#include <clang/Basic/Diagnostic.h>


namespace tfscr
{
	struct DiagnosticInfo
	{
		std::string message;
		std::string fileName;
		int line;
		int column;
	};



	class TfscrDiagnosticListener
	{
	public:


		virtual void onDiagnostic(const DiagnosticInfo & info)
		{
		}
	};



	class CustomDiagnosticConsumer: public clang::DiagnosticConsumer
	{
	public:

		CustomDiagnosticConsumer(TfscrDiagnosticListener * listener = 0);

		void setListener(TfscrDiagnosticListener * listener);

		virtual void HandleDiagnostic(clang::DiagnosticsEngine::Level diagLevel, const clang::Diagnostic & info);

		virtual CustomDiagnosticConsumer * clone(clang::DiagnosticsEngine & Diags) const;

	private:

		TfscrDiagnosticListener * mListener;

	};
}

#endif /* LIB_TFSCR_CUSTOM_DIAGNOSTIC_CONSUMER_H */
