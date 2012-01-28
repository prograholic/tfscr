#include "MainWindow.h"

#include <QFile>
#include <QTextDocument>
#include <QTextBlock>

MainWindow::MainWindow(tfscr::ClangFacade & clangFacade, QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mClangFacade(clangFacade)
{
	setupUi();
	loadFile();
}



void MainWindow::setupUi()
{
	ui->setupUi(this);
}



void MainWindow::loadFile()
{
	QFile data(mClangFacade.fileName());
	if (data.open(QIODevice::ReadOnly))
	{
		QByteArray content = data.readAll();

		QTextDocument * doc = ui->textEdit->document();
		ui->textEdit->setText(content);

		tfscr::VarDeclList varList = mClangFacade.varList();

		for (tfscr::VarDeclList::const_iterator it = varList.begin(); it != varList.end(); ++it)
		{
			clang::VarDecl * varDecl = *it;

			clang::SourceRange varLocation = varDecl->getSourceRange();

			clang::SourceManager & srcMgr = mClangFacade.sourceManager();

			clang::PresumedLoc locStart = srcMgr.getPresumedLoc(varLocation.getBegin());
			clang::PresumedLoc locEnd = srcMgr.getPresumedLoc(varLocation.getEnd());

			QTextBlock blkStart = doc->findBlockByLineNumber(locStart.getLine() - 1);

			int start = blkStart.position() + locStart.getColumn() - 1;
			int end = blkStart.position() + locEnd.getColumn() - 1;

			QTextCursor cursor = ui->textEdit->textCursor();
			cursor.clearSelection();

			cursor.setPosition(start);
			cursor.setPosition(end, QTextCursor::KeepAnchor);

			QTextCharFormat fmt = cursor.charFormat();
			fmt.setForeground(QBrush(QColor(Qt::red)));
			cursor.setCharFormat(fmt);
			cursor.clearSelection();

			ui->textEdit->setTextCursor(cursor);
		}
	}
}
