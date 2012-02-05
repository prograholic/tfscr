#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include "ClangFacade.h"

class MainWindow : public QMainWindow, public tfscr::VariablesVisitor
{
	Q_OBJECT
public:
	explicit MainWindow(tfscr::ClangFacade & clangFacade, const QString & fileName, QWidget * parent = 0);

signals:

	void fileLoaded();

public slots:


	void repaintDocument();



private:


	Ui::MainWindow * ui;
	tfscr::ClangFacade & mClangFacade;
	QString mFileName;


	void setupUi();
	void setupSignals();


	void loadFile();






	virtual void onFunctionParam(clang::ParmVarDecl * param);

	virtual void onVariableDeclaration(clang::VarDecl * varDecl);

	virtual void onArraySubscriptExpr(clang::ArraySubscriptExpr * arraySubscriptExpr);


	void repaintTextBlock(int start, int end, const QColor & c);

};

#endif // UIMAINWINDOW_H
