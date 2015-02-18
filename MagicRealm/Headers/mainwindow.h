#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

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

	void on_gameQuitButton_clicked();

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H
