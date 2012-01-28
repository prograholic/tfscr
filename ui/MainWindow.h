#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

#include "ClangFacade.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(tfscr::ClangFacade & clangFacade, QWidget *parent = 0);

signals:

public slots:



private:


	Ui::MainWindow * ui;
	tfscr::ClangFacade & mClangFacade;


	void setupUi();


	void loadFile();

};

#endif // UIMAINWINDOW_H
