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
    QWidget *loadingWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *loadingLoadingLabel;
    QLabel *loadingProgLabel;
    QWidget *characterSelectWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
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
        loadingWidget = new QWidget(centralWidget);
        loadingWidget->setObjectName(QStringLiteral("loadingWidget"));
        loadingWidget->setGeometry(QRect(0, 0, 800, 409));
        verticalLayout_2 = new QVBoxLayout(loadingWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 165, -1, 165);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        loadingLoadingLabel = new QLabel(loadingWidget);
        loadingLoadingLabel->setObjectName(QStringLiteral("loadingLoadingLabel"));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Serif"));
        font3.setPointSize(20);
        loadingLoadingLabel->setFont(font3);
        loadingLoadingLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(loadingLoadingLabel);

        loadingProgLabel = new QLabel(loadingWidget);
        loadingProgLabel->setObjectName(QStringLiteral("loadingProgLabel"));
        QFont font4;
        font4.setFamily(QStringLiteral("MS Serif"));
        font4.setPointSize(28);
        loadingProgLabel->setFont(font4);
        loadingProgLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(loadingProgLabel);


        verticalLayout_2->addLayout(verticalLayout);

        characterSelectWidget = new QWidget(centralWidget);
        characterSelectWidget->setObjectName(QStringLiteral("characterSelectWidget"));
        characterSelectWidget->setGeometry(QRect(0, 0, 800, 409));
        horizontalLayout_2 = new QHBoxLayout(characterSelectWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(40, -1, 40, -1);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        characterListView = new QListWidget(characterSelectWidget);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/characters/amazon.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font5;
        font5.setFamily(QStringLiteral("MS Serif"));
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(characterListView);
        __qlistwidgetitem->setFont(font5);
        __qlistwidgetitem->setIcon(icon);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/characters/black_knight.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(characterListView);
        __qlistwidgetitem1->setFont(font5);
        __qlistwidgetitem1->setIcon(icon1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/characters/captain.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(characterListView);
        __qlistwidgetitem2->setFont(font5);
        __qlistwidgetitem2->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/characters/dwarf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(characterListView);
        __qlistwidgetitem3->setFont(font5);
        __qlistwidgetitem3->setIcon(icon3);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/characters/elf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(characterListView);
        __qlistwidgetitem4->setFont(font5);
        __qlistwidgetitem4->setIcon(icon4);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/characters/swordsman.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(characterListView);
        __qlistwidgetitem5->setFont(font5);
        __qlistwidgetitem5->setIcon(icon5);
        characterListView->setObjectName(QStringLiteral("characterListView"));

        verticalLayout_3->addWidget(characterListView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        characterSelectButton = new QPushButton(characterSelectWidget);
        characterSelectButton->setObjectName(QStringLiteral("characterSelectButton"));
        QFont font6;
        font6.setFamily(QStringLiteral("MS Serif"));
        font6.setPointSize(18);
        characterSelectButton->setFont(font6);

        horizontalLayout->addWidget(characterSelectButton);

        characterQuitButton = new QPushButton(characterSelectWidget);
        characterQuitButton->setObjectName(QStringLiteral("characterQuitButton"));
        characterQuitButton->setFont(font6);

        horizontalLayout->addWidget(characterQuitButton);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout_3->setStretch(0, 8);
        verticalLayout_3->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout_3);

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
        pushButton->setText(QApplication::translate("MainWindowClass", "PushButton", 0));
        gameQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
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
