/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionExit;
    QWidget *centralWidget;
    QWidget *menuWidget;
    QVBoxLayout *verticalLayout_5;
    QLabel *menuTitleLabel;
    QVBoxLayout *menuButtonLayout;
    QPushButton *menuPlayButton;
    QPushButton *menuQuitButton;
    QWidget *gameWidget;
    QVBoxLayout *verticalLayout_6;
    QGraphicsView *graphicsView;
    QHBoxLayout *gameButtonLayout;
    QPushButton *pushButton;
    QPushButton *gameQuitButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(800, 450);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        menuWidget = new QWidget(centralWidget);
        menuWidget->setObjectName(QStringLiteral("menuWidget"));
        menuWidget->setGeometry(QRect(9, 9, 781, 401));
        sizePolicy.setHeightForWidth(menuWidget->sizePolicy().hasHeightForWidth());
        menuWidget->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(menuWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        menuTitleLabel = new QLabel(menuWidget);
        menuTitleLabel->setObjectName(QStringLiteral("menuTitleLabel"));
        QFont font;
        font.setFamily(QStringLiteral("MS Serif"));
        font.setPointSize(36);
        font.setBold(true);
        font.setWeight(75);
        menuTitleLabel->setFont(font);
        menuTitleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(menuTitleLabel);

        menuButtonLayout = new QVBoxLayout();
        menuButtonLayout->setSpacing(8);
        menuButtonLayout->setObjectName(QStringLiteral("menuButtonLayout"));
        menuButtonLayout->setContentsMargins(300, 100, 300, 100);
        menuPlayButton = new QPushButton(menuWidget);
        menuPlayButton->setObjectName(QStringLiteral("menuPlayButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(menuPlayButton->sizePolicy().hasHeightForWidth());
        menuPlayButton->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamily(QStringLiteral("MS Serif"));
        font1.setPointSize(16);
        menuPlayButton->setFont(font1);

        menuButtonLayout->addWidget(menuPlayButton);

        menuQuitButton = new QPushButton(menuWidget);
        menuQuitButton->setObjectName(QStringLiteral("menuQuitButton"));
        sizePolicy1.setHeightForWidth(menuQuitButton->sizePolicy().hasHeightForWidth());
        menuQuitButton->setSizePolicy(sizePolicy1);
        menuQuitButton->setFont(font1);

        menuButtonLayout->addWidget(menuQuitButton);


        verticalLayout_5->addLayout(menuButtonLayout);

        gameWidget = new QWidget(centralWidget);
        gameWidget->setObjectName(QStringLiteral("gameWidget"));
        gameWidget->setGeometry(QRect(0, 0, 800, 409));
        verticalLayout_6 = new QVBoxLayout(gameWidget);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        graphicsView = new QGraphicsView(gameWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        verticalLayout_6->addWidget(graphicsView);

        gameButtonLayout = new QHBoxLayout();
        gameButtonLayout->setSpacing(6);
        gameButtonLayout->setObjectName(QStringLiteral("gameButtonLayout"));
        pushButton = new QPushButton(gameWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Serif"));
        pushButton->setFont(font2);

        gameButtonLayout->addWidget(pushButton);

        gameQuitButton = new QPushButton(gameWidget);
        gameQuitButton->setObjectName(QStringLiteral("gameQuitButton"));
        gameQuitButton->setFont(font2);

        gameButtonLayout->addWidget(gameQuitButton);


        verticalLayout_6->addLayout(gameButtonLayout);

        verticalLayout_6->setStretch(0, 7);
        verticalLayout_6->setStretch(1, 1);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionExit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Magic Realm", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Q", 0));
        menuTitleLabel->setText(QApplication::translate("MainWindowClass", "Magic Realm", 0));
        menuPlayButton->setText(QApplication::translate("MainWindowClass", "Play", 0));
        menuQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
        pushButton->setText(QApplication::translate("MainWindowClass", "PushButton", 0));
        gameQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
