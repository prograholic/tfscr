#include "MainWindow.h"

#include <QFile>
#include <QTextDocument>
#include <QTextBlock>

MainWindow::MainWindow(tfscr::ClangFacade & clangFacade, const QString & fileName, QWidget * parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mClangFacade(clangFacade),
	mFileName(fileName)
{
	setupUi();
	setupSignals();

	loadFile();
}

void MainWindow::repaintDocument()
{
	mClangFacade.parseAST(mFileName.toLocal8Bit().data(), this);
}



void MainWindow::setupUi()
{
	ui->setupUi(this);
}

void MainWindow::setupSignals()
{
	connect(this, SIGNAL(fileLoaded()), SLOT(repaintDocument()));
}



void MainWindow::loadFile()
{
	QFile data(mFileName);
	if (data.open(QIODevice::ReadOnly))
	{
		QByteArray content = data.readAll();

		ui->textEdit->setText(content);

		emit fileLoaded();
	}
}



void MainWindow::onFunctionParam(clang::ParmVarDecl * param)
{
	this->onVariableDeclaration(param);
}

void MainWindow::onVariableDeclaration(clang::VarDecl * varDecl)
{
	clang::PresumedLoc locStart = mClangFacade.sourceManager().getPresumedLoc(varDecl->getLocation());

	QTextDocument * doc = ui->textEdit->document();
	QTextBlock blkStart = doc->findBlockByLineNumber(locStart.getLine() - 1);

	int start = blkStart.position() + locStart.getColumn() - 1;
	int end = start + varDecl->getName().size();

	repaintTextBlock(start, end, QColor(Qt::red));
}

void MainWindow::onArraySubscriptExpr(clang::ArraySubscriptExpr * arraySubscriptExpr)
{
	clang::SourceRange range = arraySubscriptExpr->getSourceRange();

	clang::PresumedLoc locStart = mClangFacade.sourceManager().getPresumedLoc(range.getBegin());
	clang::PresumedLoc locEnd = mClangFacade.sourceManager().getPresumedLoc(range.getEnd());

	QTextDocument * doc = ui->textEdit->document();

	QTextBlock blkStart = doc->findBlockByLineNumber(locStart.getLine() - 1);
	int start = blkStart.position() + locStart.getColumn() - 1;

	QTextBlock blkEnd = doc->findBlockByLineNumber(locEnd.getLine() - 1);
	int end = blkEnd.position() + locEnd.getColumn();

	repaintTextBlock(start, end, QColor(Qt::green));
}




void MainWindow::repaintTextBlock(int start, int end, const QColor & c)
{
	QTextCursor cursor = ui->textEdit->textCursor();
	cursor.clearSelection();

	cursor.setPosition(start);
	cursor.setPosition(end, QTextCursor::KeepAnchor);

	QTextCharFormat fmt = cursor.charFormat();
	fmt.setForeground(QBrush(c));
	cursor.setCharFormat(fmt);
	cursor.clearSelection();

	ui->textEdit->setTextCursor(cursor);
}
