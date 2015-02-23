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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
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
    QHBoxLayout *gameWidgetLayout;
    QVBoxLayout *gameViewLayout;
    QGraphicsView *graphicsView;
    QGroupBox *actionsGroupBox;
    QHBoxLayout *actionsLayout;
    QPushButton *gameMoveActionButton;
    QPushButton *gameSearchActionButton;
    QPushButton *gameTradeActionButton;
    QPushButton *gameHideActionButton;
    QPushButton *gameSubmitTurnButton;
    QPushButton *gameQuitButton;
    QVBoxLayout *gameInfoPhaseLayout;
    QTabWidget *informationTabWidget;
    QWidget *characterInfoTab;
    QVBoxLayout *verticalLayout_3;
    QTextBrowser *gameCharacterInformationBrowser;
    QWidget *tileInfoTab;
    QVBoxLayout *verticalLayout;
    QTextBrowser *gameTileInformationBrowser;
    QComboBox *gamePhaseComboBox;
    QGroupBox *gameEventFeedGroupBox;
    QVBoxLayout *verticalLayout_4;
    QTextBrowser *gameEventFeedBrowser;
    QWidget *loadingWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *loadingLabelLayout;
    QLabel *loadingLoadingLabel;
    QLabel *loadingMessageLabel;
    QLabel *loadingProgLabel;
    QWidget *characterSelectWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *characterSelectorLayout;
    QLabel *characterSelectCharacterLabel;
    QListWidget *characterListView;
    QLabel *characterSelectStartLocationsLabel;
    QListWidget *characterStartLocationListView;
    QHBoxLayout *characterSelectorButtonsLayout;
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
        menuPlayButton->setToolTipDuration(-1);

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
        gameWidgetLayout = new QHBoxLayout(gameWidget);
        gameWidgetLayout->setSpacing(6);
        gameWidgetLayout->setContentsMargins(11, 11, 11, 11);
        gameWidgetLayout->setObjectName(QStringLiteral("gameWidgetLayout"));
        gameViewLayout = new QVBoxLayout();
        gameViewLayout->setSpacing(6);
        gameViewLayout->setObjectName(QStringLiteral("gameViewLayout"));
        graphicsView = new QGraphicsView(gameWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gameViewLayout->addWidget(graphicsView);

        actionsGroupBox = new QGroupBox(gameWidget);
        actionsGroupBox->setObjectName(QStringLiteral("actionsGroupBox"));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Serif"));
        actionsGroupBox->setFont(font2);
        actionsLayout = new QHBoxLayout(actionsGroupBox);
        actionsLayout->setSpacing(1);
        actionsLayout->setContentsMargins(11, 11, 11, 11);
        actionsLayout->setObjectName(QStringLiteral("actionsLayout"));
        actionsLayout->setContentsMargins(1, 1, 1, 1);
        gameMoveActionButton = new QPushButton(actionsGroupBox);
        gameMoveActionButton->setObjectName(QStringLiteral("gameMoveActionButton"));
        gameMoveActionButton->setFont(font2);
        gameMoveActionButton->setAutoFillBackground(true);
        gameMoveActionButton->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/actions/move.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameMoveActionButton->setIcon(icon);
        gameMoveActionButton->setIconSize(QSize(32, 32));
        gameMoveActionButton->setAutoDefault(false);
        gameMoveActionButton->setDefault(false);
        gameMoveActionButton->setFlat(false);

        actionsLayout->addWidget(gameMoveActionButton);

        gameSearchActionButton = new QPushButton(actionsGroupBox);
        gameSearchActionButton->setObjectName(QStringLiteral("gameSearchActionButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/actions/search.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameSearchActionButton->setIcon(icon1);
        gameSearchActionButton->setIconSize(QSize(32, 32));

        actionsLayout->addWidget(gameSearchActionButton);

        gameTradeActionButton = new QPushButton(actionsGroupBox);
        gameTradeActionButton->setObjectName(QStringLiteral("gameTradeActionButton"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/actions/trade.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameTradeActionButton->setIcon(icon2);
        gameTradeActionButton->setIconSize(QSize(32, 32));

        actionsLayout->addWidget(gameTradeActionButton);

        gameHideActionButton = new QPushButton(actionsGroupBox);
        gameHideActionButton->setObjectName(QStringLiteral("gameHideActionButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/actions/hide.gif"), QSize(), QIcon::Normal, QIcon::Off);
        gameHideActionButton->setIcon(icon3);
        gameHideActionButton->setIconSize(QSize(32, 32));

        actionsLayout->addWidget(gameHideActionButton);

        gameSubmitTurnButton = new QPushButton(actionsGroupBox);
        gameSubmitTurnButton->setObjectName(QStringLiteral("gameSubmitTurnButton"));
        QFont font3;
        font3.setFamily(QStringLiteral("MS Serif"));
        font3.setPointSize(22);
        font3.setBold(true);
        font3.setWeight(75);
        gameSubmitTurnButton->setFont(font3);

        actionsLayout->addWidget(gameSubmitTurnButton);

        gameQuitButton = new QPushButton(actionsGroupBox);
        gameQuitButton->setObjectName(QStringLiteral("gameQuitButton"));
        gameQuitButton->setFont(font3);

        actionsLayout->addWidget(gameQuitButton);

        gameSubmitTurnButton->raise();
        gameHideActionButton->raise();
        gameMoveActionButton->raise();
        gameQuitButton->raise();
        gameSearchActionButton->raise();
        gameTradeActionButton->raise();

        gameViewLayout->addWidget(actionsGroupBox);

        gameViewLayout->setStretch(0, 6);
        gameViewLayout->setStretch(1, 1);

        gameWidgetLayout->addLayout(gameViewLayout);

        gameInfoPhaseLayout = new QVBoxLayout();
        gameInfoPhaseLayout->setSpacing(6);
        gameInfoPhaseLayout->setObjectName(QStringLiteral("gameInfoPhaseLayout"));
        gameInfoPhaseLayout->setContentsMargins(-1, -1, -1, 5);
        informationTabWidget = new QTabWidget(gameWidget);
        informationTabWidget->setObjectName(QStringLiteral("informationTabWidget"));
        informationTabWidget->setToolTipDuration(-1);
        informationTabWidget->setIconSize(QSize(32, 32));
        characterInfoTab = new QWidget();
        characterInfoTab->setObjectName(QStringLiteral("characterInfoTab"));
        verticalLayout_3 = new QVBoxLayout(characterInfoTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        gameCharacterInformationBrowser = new QTextBrowser(characterInfoTab);
        gameCharacterInformationBrowser->setObjectName(QStringLiteral("gameCharacterInformationBrowser"));

        verticalLayout_3->addWidget(gameCharacterInformationBrowser);

        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/tab/record.gif"), QSize(), QIcon::Normal, QIcon::Off);
        informationTabWidget->addTab(characterInfoTab, icon4, QString());
        tileInfoTab = new QWidget();
        tileInfoTab->setObjectName(QStringLiteral("tileInfoTab"));
        verticalLayout = new QVBoxLayout(tileInfoTab);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gameTileInformationBrowser = new QTextBrowser(tileInfoTab);
        gameTileInformationBrowser->setObjectName(QStringLiteral("gameTileInformationBrowser"));
        QFont font4;
        font4.setFamily(QStringLiteral("MS Serif"));
        font4.setPointSize(14);
        gameTileInformationBrowser->setFont(font4);

        verticalLayout->addWidget(gameTileInformationBrowser);

        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/tiles/questionmark.gif"), QSize(), QIcon::Normal, QIcon::Off);
        informationTabWidget->addTab(tileInfoTab, icon5, QString());

        gameInfoPhaseLayout->addWidget(informationTabWidget);

        gamePhaseComboBox = new QComboBox(gameWidget);
        gamePhaseComboBox->setObjectName(QStringLiteral("gamePhaseComboBox"));
        gamePhaseComboBox->setFont(font3);
        gamePhaseComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);
        gamePhaseComboBox->setIconSize(QSize(24, 24));
        gamePhaseComboBox->setDuplicatesEnabled(false);
        gamePhaseComboBox->setFrame(true);

        gameInfoPhaseLayout->addWidget(gamePhaseComboBox);

        gameEventFeedGroupBox = new QGroupBox(gameWidget);
        gameEventFeedGroupBox->setObjectName(QStringLiteral("gameEventFeedGroupBox"));
        gameEventFeedGroupBox->setFont(font2);
        verticalLayout_4 = new QVBoxLayout(gameEventFeedGroupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        gameEventFeedBrowser = new QTextBrowser(gameEventFeedGroupBox);
        gameEventFeedBrowser->setObjectName(QStringLiteral("gameEventFeedBrowser"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        QBrush brush2(QColor(120, 120, 120, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        QBrush brush3(QColor(240, 240, 240, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        gameEventFeedBrowser->setPalette(palette);
        QFont font5;
        font5.setPointSize(10);
        gameEventFeedBrowser->setFont(font5);

        verticalLayout_4->addWidget(gameEventFeedBrowser);


        gameInfoPhaseLayout->addWidget(gameEventFeedGroupBox);

        gameInfoPhaseLayout->setStretch(0, 6);
        gameInfoPhaseLayout->setStretch(1, 1);
        gameInfoPhaseLayout->setStretch(2, 2);

        gameWidgetLayout->addLayout(gameInfoPhaseLayout);

        gameWidgetLayout->setStretch(0, 8);
        gameWidgetLayout->setStretch(1, 5);
        loadingWidget = new QWidget(centralWidget);
        loadingWidget->setObjectName(QStringLiteral("loadingWidget"));
        loadingWidget->setGeometry(QRect(0, 0, 800, 409));
        verticalLayout_2 = new QVBoxLayout(loadingWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(9, 145, -1, 145);
        loadingLabelLayout = new QVBoxLayout();
        loadingLabelLayout->setSpacing(6);
        loadingLabelLayout->setObjectName(QStringLiteral("loadingLabelLayout"));
        loadingLoadingLabel = new QLabel(loadingWidget);
        loadingLoadingLabel->setObjectName(QStringLiteral("loadingLoadingLabel"));
        QFont font6;
        font6.setFamily(QStringLiteral("MS Serif"));
        font6.setPointSize(20);
        loadingLoadingLabel->setFont(font6);
        loadingLoadingLabel->setAlignment(Qt::AlignCenter);

        loadingLabelLayout->addWidget(loadingLoadingLabel);

        loadingMessageLabel = new QLabel(loadingWidget);
        loadingMessageLabel->setObjectName(QStringLiteral("loadingMessageLabel"));
        QFont font7;
        font7.setFamily(QStringLiteral("MS Serif"));
        font7.setPointSize(22);
        loadingMessageLabel->setFont(font7);
        loadingMessageLabel->setAlignment(Qt::AlignCenter);

        loadingLabelLayout->addWidget(loadingMessageLabel);

        loadingProgLabel = new QLabel(loadingWidget);
        loadingProgLabel->setObjectName(QStringLiteral("loadingProgLabel"));
        QFont font8;
        font8.setFamily(QStringLiteral("MS Serif"));
        font8.setPointSize(28);
        loadingProgLabel->setFont(font8);
        loadingProgLabel->setAlignment(Qt::AlignCenter);

        loadingLabelLayout->addWidget(loadingProgLabel);


        verticalLayout_2->addLayout(loadingLabelLayout);

        characterSelectWidget = new QWidget(centralWidget);
        characterSelectWidget->setObjectName(QStringLiteral("characterSelectWidget"));
        characterSelectWidget->setGeometry(QRect(0, 0, 800, 409));
        horizontalLayout_2 = new QHBoxLayout(characterSelectWidget);
        horizontalLayout_2->setSpacing(20);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(30, -1, 30, -1);
        characterSelectorLayout = new QVBoxLayout();
        characterSelectorLayout->setSpacing(6);
        characterSelectorLayout->setObjectName(QStringLiteral("characterSelectorLayout"));
        characterSelectCharacterLabel = new QLabel(characterSelectWidget);
        characterSelectCharacterLabel->setObjectName(QStringLiteral("characterSelectCharacterLabel"));
        QFont font9;
        font9.setFamily(QStringLiteral("MS Serif"));
        font9.setPointSize(18);
        font9.setBold(true);
        font9.setWeight(75);
        characterSelectCharacterLabel->setFont(font9);

        characterSelectorLayout->addWidget(characterSelectCharacterLabel);

        characterListView = new QListWidget(characterSelectWidget);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/characters/amazon.png"), QSize(), QIcon::Normal, QIcon::Off);
        QFont font10;
        font10.setFamily(QStringLiteral("MS Serif"));
        font10.setPointSize(16);
        font10.setBold(true);
        font10.setWeight(75);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(characterListView);
        __qlistwidgetitem->setFont(font10);
        __qlistwidgetitem->setIcon(icon6);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/characters/black_knight.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(characterListView);
        __qlistwidgetitem1->setFont(font10);
        __qlistwidgetitem1->setIcon(icon7);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/characters/captain.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(characterListView);
        __qlistwidgetitem2->setFont(font10);
        __qlistwidgetitem2->setIcon(icon8);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/characters/dwarf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(characterListView);
        __qlistwidgetitem3->setFont(font10);
        __qlistwidgetitem3->setIcon(icon9);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/characters/elf.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(characterListView);
        __qlistwidgetitem4->setFont(font10);
        __qlistwidgetitem4->setIcon(icon10);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/characters/swordsman.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(characterListView);
        __qlistwidgetitem5->setFont(font10);
        __qlistwidgetitem5->setIcon(icon11);
        characterListView->setObjectName(QStringLiteral("characterListView"));
        characterListView->setFont(font10);

        characterSelectorLayout->addWidget(characterListView);

        characterSelectStartLocationsLabel = new QLabel(characterSelectWidget);
        characterSelectStartLocationsLabel->setObjectName(QStringLiteral("characterSelectStartLocationsLabel"));
        characterSelectStartLocationsLabel->setFont(font1);

        characterSelectorLayout->addWidget(characterSelectStartLocationsLabel);

        characterStartLocationListView = new QListWidget(characterSelectWidget);
        new QListWidgetItem(characterStartLocationListView);
        characterStartLocationListView->setObjectName(QStringLiteral("characterStartLocationListView"));
        QFont font11;
        font11.setFamily(QStringLiteral("MS Serif"));
        font11.setPointSize(12);
        font11.setBold(false);
        font11.setWeight(50);
        characterStartLocationListView->setFont(font11);

        characterSelectorLayout->addWidget(characterStartLocationListView);

        characterSelectorButtonsLayout = new QHBoxLayout();
        characterSelectorButtonsLayout->setSpacing(6);
        characterSelectorButtonsLayout->setObjectName(QStringLiteral("characterSelectorButtonsLayout"));
        characterSelectButton = new QPushButton(characterSelectWidget);
        characterSelectButton->setObjectName(QStringLiteral("characterSelectButton"));
        QFont font12;
        font12.setFamily(QStringLiteral("MS Serif"));
        font12.setPointSize(18);
        characterSelectButton->setFont(font12);

        characterSelectorButtonsLayout->addWidget(characterSelectButton);

        characterQuitButton = new QPushButton(characterSelectWidget);
        characterQuitButton->setObjectName(QStringLiteral("characterQuitButton"));
        characterQuitButton->setFont(font12);

        characterSelectorButtonsLayout->addWidget(characterQuitButton);


        characterSelectorLayout->addLayout(characterSelectorButtonsLayout);

        characterSelectorLayout->setStretch(0, 1);
        characterSelectorLayout->setStretch(1, 8);
        characterSelectorLayout->setStretch(2, 1);
        characterSelectorLayout->setStretch(3, 4);
        characterSelectorLayout->setStretch(4, 1);

        horizontalLayout_2->addLayout(characterSelectorLayout);

        characterDetailView = new QLabel(characterSelectWidget);
        characterDetailView->setObjectName(QStringLiteral("characterDetailView"));
        characterDetailView->setPixmap(QPixmap(QString::fromUtf8(":/images/characterdetail/amazon.jpg")));
        characterDetailView->setScaledContents(true);

        horizontalLayout_2->addWidget(characterDetailView);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 9);
        MainWindowClass->setCentralWidget(centralWidget);
        characterSelectWidget->raise();
        loadingWidget->raise();
        menuWidget->raise();
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

        informationTabWidget->setCurrentIndex(0);
        characterListView->setCurrentRow(0);
        characterStartLocationListView->setCurrentRow(0);


        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Magic Realm", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0));
        actionExit->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+Q", 0));
        menuTitleLabel->setText(QApplication::translate("MainWindowClass", "Magic Realm", 0));
#ifndef QT_NO_TOOLTIP
        menuPlayButton->setToolTip(QApplication::translate("MainWindowClass", "SHELLY", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        menuPlayButton->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        menuPlayButton->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        menuPlayButton->setText(QApplication::translate("MainWindowClass", "Play", 0));
        menuQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
        actionsGroupBox->setTitle(QApplication::translate("MainWindowClass", "Actions", 0));
#ifndef QT_NO_TOOLTIP
        gameMoveActionButton->setToolTip(QApplication::translate("MainWindowClass", "Move", 0));
#endif // QT_NO_TOOLTIP
        gameMoveActionButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        gameSearchActionButton->setToolTip(QApplication::translate("MainWindowClass", "Search", 0));
#endif // QT_NO_TOOLTIP
        gameSearchActionButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        gameTradeActionButton->setToolTip(QApplication::translate("MainWindowClass", "Trade", 0));
#endif // QT_NO_TOOLTIP
        gameTradeActionButton->setText(QString());
#ifndef QT_NO_TOOLTIP
        gameHideActionButton->setToolTip(QApplication::translate("MainWindowClass", "Hide", 0));
#endif // QT_NO_TOOLTIP
        gameHideActionButton->setText(QString());
        gameSubmitTurnButton->setText(QApplication::translate("MainWindowClass", "Submit", 0));
        gameQuitButton->setText(QApplication::translate("MainWindowClass", "Quit", 0));
#ifndef QT_NO_TOOLTIP
        informationTabWidget->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        informationTabWidget->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        informationTabWidget->setTabText(informationTabWidget->indexOf(characterInfoTab), QString());
        informationTabWidget->setTabToolTip(informationTabWidget->indexOf(characterInfoTab), QApplication::translate("MainWindowClass", "Character Info", 0));
        gameTileInformationBrowser->setHtml(QApplication::translate("MainWindowClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Serif'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        informationTabWidget->setTabText(informationTabWidget->indexOf(tileInfoTab), QString());
        informationTabWidget->setTabToolTip(informationTabWidget->indexOf(tileInfoTab), QApplication::translate("MainWindowClass", "Tile Info", 0));
        gamePhaseComboBox->setCurrentText(QString());
        gameEventFeedGroupBox->setTitle(QApplication::translate("MainWindowClass", "Event Feed", 0));
        loadingLoadingLabel->setText(QApplication::translate("MainWindowClass", "Loading", 0));
        loadingMessageLabel->setText(QString());
        loadingProgLabel->setText(QApplication::translate("MainWindowClass", "...", 0));
        characterSelectCharacterLabel->setText(QApplication::translate("MainWindowClass", "Characters", 0));

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

        characterSelectStartLocationsLabel->setText(QApplication::translate("MainWindowClass", "Start Locations", 0));

        const bool __sortingEnabled1 = characterStartLocationListView->isSortingEnabled();
        characterStartLocationListView->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem6 = characterStartLocationListView->item(0);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindowClass", "Inn", 0));
        characterStartLocationListView->setSortingEnabled(__sortingEnabled1);

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
