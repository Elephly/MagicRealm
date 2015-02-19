#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "shared.h"
#include "gameWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
    void on_actionExit_triggered();

	void on_menuPlayButton_clicked();
	void on_menuQuitButton_clicked();

	void on_characterSelectButton_clicked();
	void on_characterQuitButton_clicked();
	void on_characterListView_currentRowChanged(int row);

	void on_gameQuitButton_clicked();

private:
	Ui::MainWindowClass ui;
	GameWindow* gameWindow;

	static QString characterDetailPaths[];
};

#endif // MAINWINDOW_H
