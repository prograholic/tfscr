#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>

#include "MainWindow.h"

#include "ClangFacade.h"



int main(int argc, char * argv [])
{
	QApplication app(argc, argv);

	QString file = QFileDialog::getOpenFileName();
	if (!file.isEmpty())
	{
		tfscr::ClangFacade clangFacade;
		clangFacade.parseAST(file.toLocal8Bit().data());


		MainWindow mainWindow(clangFacade);
		mainWindow.show();
		return app.exec();
	}
	else
	{
		QMessageBox::warning(0, "", "Need to select file");
	}

	return 0;
}
