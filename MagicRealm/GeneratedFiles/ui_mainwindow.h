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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
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
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *gameViewLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *gameButtonLayout;
    QPushButton *gameMoveActionButton;
    QPushButton *gameSearchActionButton;
    QPushButton *gameTradeActionButton;
    QPushButton *gameHideActionButton;
    QPushButton *gamePeerActionButton;
    QPushButton *gameQuitButton;
    QTextBrowser *tileInformationBrowser;
    QWidget *loadingWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *loadingLabelLayout;
    QLabel *loadingLoadingLabel;
    QLabel *loadingProgLabel;
    QWidget *characterSelectWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *characterSelectorLayout;
    QListWidget *characterListView;
    QHBoxLayout *horizontalLayout;
    QPushButton *characterSelectButton;
    QPushButton *characterQuitButton;
    QLabel *characterDetailView;
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
        horizontalLayout_3 = new QHBoxLayout(gameWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gameViewLayout = new QVBoxLayout();
        gameViewLayout->setSpacing(6);
        gameViewLayout->setObjectName(QStringLiteral("gameViewLayout"));
        graphicsView = new QGraphicsView(gameWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gameViewLayout->addWidget(graphicsView);

        gameButtonLayout = new QHBoxLayout();
        gameButtonLayout->setSpacing(6);
        gameButtonLayout->setObjectName(QStringLiteral("gameButtonLayout"));
        gameMoveActionButton = new QPushButton(gameWidget);
        gameMoveActionButton->setObjectName(QStringLiteral("gameMoveActionButton"));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Serif"));
        gameMoveActionButton->setFont(font2);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/actions/move.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameMoveActionButton->setIcon(icon);
        gameMoveActionButton->setIconSize(QSize(32, 32));

        gameButtonLayout->addWidget(gameMoveActionButton);

        gameSearchActionButton = new QPushButton(gameWidget);
        gameSearchActionButton->setObjectName(QStringLiteral("gameSearchActionButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/actions/search.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameSearchActionButton->setIcon(icon1);
        gameSearchActionButton->setIconSize(QSize(32, 32));

        gameButtonLayout->addWidget(gameSearchActionButton);

        gameTradeActionButton = new QPushButton(gameWidget);
        gameTradeActionButton->setObjectName(QStringLiteral("gameTradeActionButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/actions/trade.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameTradeActionButton->setIcon(icon2);
        gameTradeActionButton->setIconSize(QSize(32, 32));

        gameButtonLayout->addWidget(gameTradeActionButton);

        gameHideActionButton = new QPushButton(gameWidget);
        gameHideActionButton->setObjectName(QStringLiteral("gameHideActionButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/actions/hide.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameHideActionButton->setIcon(icon3);
        gameHideActionButton->setIconSize(QSize(32, 32));

        gameButtonLayout->addWidget(gameHideActionButton);

        gamePeerActionButton = new QPushButton(gameWidget);
        gamePeerActionButton->setObjectName(QStringLiteral("gamePeerActionButton"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/actions/peer.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gamePeerActionButton->setIcon(icon4);
        gamePeerActionButton->setIconSize(QSize(32, 32));

        gameButtonLayout->addWidget(gamePeerActionButton);

        gameQuitButton = new QPushButton(gameWidget);
        gameQuitButton->setObjectName(QStringLiteral("gameQuitButton"));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Serif"));
        font3.setPointSize(22);
        font3.setBold(true);
        font3.setWeight(75);
        gameQuitButton->setFont(font3);

        gameButtonLayout->addWidget(gameQuitButton);


        gameViewLayout->addLayout(gameButtonLayout);


        horizontalLayout_3->addLayout(gameViewLayout);

        tileInformationBrowser = new QTextBrowser(gameWidget);
        tileInformationBrowser->setObjectName(QStringLiteral("tileInformationBrowser"));
        QFont font4;
        font4.setFamily(QStringLiteral("MS Serif"));
        font4.setPointSize(14);
        tileInformationBrowser->setFont(font4);

        horizontalLayout_3->addWidget(tileInformationBrowser);

        horizontalLayout_3->setStretch(0, 7);
        horizontalLayout_3->setStretch(1, 3);
        loadingWidget = new QWidget(centralWidget);
        loadingWidget->setObjectName(QStringLiteral("loadingWidget"));
        loadingWidget->setGeometry(QRect(0, 0, 800, 409));
        verticalLayout_2 = new QVBoxLayout(loadingWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 165, -1, 165);
        loadingLabelLayout = new QVBoxLayout();
        loadingLabelLayout->setSpacing(6);
        loadingLabelLayout->setObjectName(QStringLiteral("loadingLabelLayout"));
        loadingLoadingLabel = new QLabel(loadingWidget);
        loadingLoadingLabel->setObjectName(QStringLiteral("loadingLoadingLabel"));
        QFont font5;
        font5.setFamily(QStringLiteral("MS Serif"));
        font5.setPointSize(20);
        loadingLoadingLabel->setFont(font5);
        loadingLoadingLabel->setAlignment(Qt::AlignCenter);

        loadingLabelLayout->addWidget(loadingLoadingLabel);

        loadingProgLabel = new QLabel(loadingWidget);
        loadingProgLabel->setObjectName(QStringLiteral("loadingProgLabel"));
        QFont font6;
        font6.setFamily(QStringLiteral("MS Serif"));
        font6.setPointSize(28);
        loadingProgLabel->setFont(font6);
        loadingProgLabel->setAlignment(Qt::AlignCenter);

        loadingLabelLayout->addWidget(loadingProgLabel);


        verticalLayout_2->addLayout(loadingLabelLayout);

        characterSelectWidget = new QWidget(centralWidget);
        characterSelectWidget->setObjectName(QStringLiteral("characterSelectWidget"));
        characterSelectWidget->setGeometry(QRect(0, 0, 800, 409));
        horizontalLayout_2 = new QHBoxLayout(characterSelectWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(40, -1, 40, -1);
        characterSelectorLayout = new QVBoxLayout();
        characterSelectorLayout->setSpacing(6);
        characterSelectorLayout->setObjectName(QStringLiteral("characterSelectorLayout"));
        characterListView = new QListWidget(characterSelectWidget);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/characters/amazon.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font7;
        font7.setFamily(QStringLiteral("MS Serif"));
        font7.setPointSize(16);
        font7.setBold(true);
        font7.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(characterListView);
        __qlistwidgetitem->setFont(font7);
        __qlistwidgetitem->setIcon(icon5);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/characters/black_knight.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(characterListView);
        __qlistwidgetitem1->setFont(font7);
        __qlistwidgetitem1->setIcon(icon6);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/characters/captain.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(characterListView);
        __qlistwidgetitem2->setFont(font7);
        __qlistwidgetitem2->setIcon(icon7);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/characters/dwarf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(characterListView);
        __qlistwidgetitem3->setFont(font7);
        __qlistwidgetitem3->setIcon(icon8);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/characters/elf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(characterListView);
        __qlistwidgetitem4->setFont(font7);
        __qlistwidgetitem4->setIcon(icon9);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/characters/swordsman.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(characterListView);
        __qlistwidgetitem5->setFont(font7);
        __qlistwidgetitem5->setIcon(icon10);
        characterListView->setObjectName(QStringLiteral("characterListView"));

        characterSelectorLayout->addWidget(characterListView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        characterSelectButton = new QPushButton(characterSelectWidget);
        characterSelectButton->setObjectName(QStringLiteral("characterSelectButton"));
        QFont font8;
        font8.setFamily(QStringLiteral("MS Serif"));
        font8.setPointSize(18);
        characterSelectButton->setFont(font8);

        horizontalLayout->addWidget(characterSelectButton);

        characterQuitButton = new QPushButton(characterSelectWidget);
        characterQuitButton->setObjectName(QStringLiteral("characterQuitButton"));
        characterQuitButton->setFont(font8);

        horizontalLayout->addWidget(characterQuitButton);


        characterSelectorLayout->addLayout(horizontalLayout);

        characterSelectorLayout->setStretch(0, 8);
        characterSelectorLayout->setStretch(1, 1);

        horizontalLayout_2->addLayout(characterSelectorLayout);

        characterDetailView = new QLabel(characterSelectWidget);
        characterDetailView->setObjectName(QStringLiteral("characterDetailView"));
        characterDetailView->setPixmap(QPixmap(QString::fromUtf8(":/images/characterdetail/amazon.jpg")));
        characterDetailView->setScaledContents(true);

        horizontalLayout_2->addWidget(characterDetailView);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 9);
        MainWindowClass->setCentralWidget(centralWidget);
        menuWidget->raise();
        loadingWidget->raise();
        characterSelectWidget->raise();
        gameWidget->raise();
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

        characterListView->setCurrentRow(0);


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
        gameMoveActionButton->setText(QString());
        gameSearchActionButton->setText(QString());
        gameTradeActionButton->setText(QString());
        gameHideActionButton->setText(QString());
        gamePeerActionButton->setText(QString());
        gameQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
        tileInformationBrowser->setHtml(QApplication::translate("MainWindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Serif'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        loadingLoadingLabel->setText(QApplication::translate("MainWindowClass", "Loading", 0));
        loadingProgLabel->setText(QApplication::translate("MainWindowClass", "...", 0));

        const bool __sortingEnabled = characterListView->isSortingEnabled();
        characterListView->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = characterListView->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindowClass", "Amazon", 0));
        QListWidgetItem *___qlistwidgetitem1 = characterListView->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindowClass", "Black Knight", 0));
        QListWidgetItem *___qlistwidgetitem2 = characterListView->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindowClass", "Captain", 0));
        QListWidgetItem *___qlistwidgetitem3 = characterListView->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindowClass", "Dwarf", 0));
        QListWidgetItem *___qlistwidgetitem4 = characterListView->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindowClass", "Elf", 0));
        QListWidgetItem *___qlistwidgetitem5 = characterListView->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindowClass", "Swordsman", 0));
        characterListView->setSortingEnabled(__sortingEnabled);

        characterSelectButton->setText(QApplication::translate("MainWindowClass", "Select", 0));
        characterQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
        characterDetailView->setText(QString());
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
