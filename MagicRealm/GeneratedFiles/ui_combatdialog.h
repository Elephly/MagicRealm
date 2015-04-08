/********************************************************************************
** Form generated from reading UI file 'combatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBATDIALOG_H
#define UI_COMBATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CombatDialog
{
public:
    QLabel *myCharacter;
    QLabel *enemyCharacter;
    QLabel *versusImage;
    QPushButton *submitButton;
    QGroupBox *encounter_runGroupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *yesRun;
    QRadioButton *noRun;
    QGroupBox *moveGroupBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *moveCounterList;
    QGroupBox *melee_fightGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *fightCounterList;
    QGroupBox *melee_moveTypeGroupBox;
    QHBoxLayout *horizontalLayout_3;
    QListWidget *moveTypeList;
    QGroupBox *melee_blockTypeGroupBox;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *blockTypeList;
    QGroupBox *melee_fightTypeGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QListWidget *fightTypeList;

    void setupUi(QDialog *CombatDialog)
    {
        if (CombatDialog->objectName().isEmpty())
            CombatDialog->setObjectName(QStringLiteral("CombatDialog"));
        CombatDialog->setWindowModality(Qt::NonModal);
        CombatDialog->resize(800, 600);
        CombatDialog->setModal(false);
        myCharacter = new QLabel(CombatDialog);
        myCharacter->setObjectName(QStringLiteral("myCharacter"));
        myCharacter->setGeometry(QRect(0, 0, 380, 600));
        myCharacter->setPixmap(QPixmap(QString::fromUtf8(":/images/characterprofile/black_knight.jpg")));
        enemyCharacter = new QLabel(CombatDialog);
        enemyCharacter->setObjectName(QStringLiteral("enemyCharacter"));
        enemyCharacter->setGeometry(QRect(420, 0, 380, 600));
        enemyCharacter->setPixmap(QPixmap(QString::fromUtf8(":/images/characterprofile/dwarf.jpg")));
        versusImage = new QLabel(CombatDialog);
        versusImage->setObjectName(QStringLiteral("versusImage"));
        versusImage->setGeometry(QRect(380, 30, 40, 75));
        versusImage->setPixmap(QPixmap(QString::fromUtf8(":/images/combat/versus.png")));
        versusImage->setScaledContents(true);
        submitButton = new QPushButton(CombatDialog);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setEnabled(true);
        submitButton->setGeometry(QRect(270, 500, 260, 60));
        QFont font;
        font.setFamily(QStringLiteral("MS Serif"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        submitButton->setFont(font);
        submitButton->setDefault(false);
        encounter_runGroupBox = new QGroupBox(CombatDialog);
        encounter_runGroupBox->setObjectName(QStringLiteral("encounter_runGroupBox"));
        encounter_runGroupBox->setGeometry(QRect(340, 380, 120, 80));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Serif"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        encounter_runGroupBox->setFont(font1);
        encounter_runGroupBox->setStyleSheet(QStringLiteral("background-color : white;"));
        encounter_runGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(encounter_runGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        yesRun = new QRadioButton(encounter_runGroupBox);
        yesRun->setObjectName(QStringLiteral("yesRun"));
        yesRun->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(yesRun);

        noRun = new QRadioButton(encounter_runGroupBox);
        noRun->setObjectName(QStringLiteral("noRun"));
        noRun->setChecked(true);

        verticalLayout->addWidget(noRun);

        moveGroupBox = new QGroupBox(CombatDialog);
        moveGroupBox->setObjectName(QStringLiteral("moveGroupBox"));
        moveGroupBox->setGeometry(QRect(300, 140, 200, 200));
        moveGroupBox->setFont(font);
        moveGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        moveGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(moveGroupBox);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        moveCounterList = new QListWidget(moveGroupBox);
        moveCounterList->setObjectName(QStringLiteral("moveCounterList"));
        QFont font2;
        font2.setFamily(QStringLiteral("MS Serif"));
        font2.setPointSize(12);
        moveCounterList->setFont(font2);

        horizontalLayout->addWidget(moveCounterList);

        melee_fightGroupBox = new QGroupBox(CombatDialog);
        melee_fightGroupBox->setObjectName(QStringLiteral("melee_fightGroupBox"));
        melee_fightGroupBox->setGeometry(QRect(550, 140, 200, 200));
        melee_fightGroupBox->setFont(font);
        melee_fightGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        melee_fightGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_2 = new QHBoxLayout(melee_fightGroupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        fightCounterList = new QListWidget(melee_fightGroupBox);
        fightCounterList->setObjectName(QStringLiteral("fightCounterList"));
        fightCounterList->setFont(font2);

        horizontalLayout_2->addWidget(fightCounterList);

        melee_moveTypeGroupBox = new QGroupBox(CombatDialog);
        melee_moveTypeGroupBox->setObjectName(QStringLiteral("melee_moveTypeGroupBox"));
        melee_moveTypeGroupBox->setGeometry(QRect(100, 375, 180, 100));
        melee_moveTypeGroupBox->setFont(font1);
        melee_moveTypeGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        melee_moveTypeGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_3 = new QHBoxLayout(melee_moveTypeGroupBox);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        moveTypeList = new QListWidget(melee_moveTypeGroupBox);
        new QListWidgetItem(moveTypeList);
        new QListWidgetItem(moveTypeList);
        new QListWidgetItem(moveTypeList);
        moveTypeList->setObjectName(QStringLiteral("moveTypeList"));
        moveTypeList->setFont(font2);

        horizontalLayout_3->addWidget(moveTypeList);

        melee_blockTypeGroupBox = new QGroupBox(CombatDialog);
        melee_blockTypeGroupBox->setObjectName(QStringLiteral("melee_blockTypeGroupBox"));
        melee_blockTypeGroupBox->setGeometry(QRect(310, 325, 180, 100));
        melee_blockTypeGroupBox->setFont(font1);
        melee_blockTypeGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        melee_blockTypeGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_4 = new QHBoxLayout(melee_blockTypeGroupBox);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        blockTypeList = new QListWidget(melee_blockTypeGroupBox);
        new QListWidgetItem(blockTypeList);
        new QListWidgetItem(blockTypeList);
        new QListWidgetItem(blockTypeList);
        blockTypeList->setObjectName(QStringLiteral("blockTypeList"));
        blockTypeList->setFont(font2);

        horizontalLayout_4->addWidget(blockTypeList);

        melee_fightTypeGroupBox = new QGroupBox(CombatDialog);
        melee_fightTypeGroupBox->setObjectName(QStringLiteral("melee_fightTypeGroupBox"));
        melee_fightTypeGroupBox->setGeometry(QRect(520, 375, 180, 100));
        melee_fightTypeGroupBox->setFont(font1);
        melee_fightTypeGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        melee_fightTypeGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout_5 = new QHBoxLayout(melee_fightTypeGroupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        fightTypeList = new QListWidget(melee_fightTypeGroupBox);
        new QListWidgetItem(fightTypeList);
        new QListWidgetItem(fightTypeList);
        new QListWidgetItem(fightTypeList);
        fightTypeList->setObjectName(QStringLiteral("fightTypeList"));
        fightTypeList->setFont(font2);

        horizontalLayout_5->addWidget(fightTypeList);


        retranslateUi(CombatDialog);

        moveTypeList->setCurrentRow(0);
        blockTypeList->setCurrentRow(-1);
        fightTypeList->setCurrentRow(0);


        QMetaObject::connectSlotsByName(CombatDialog);
    } // setupUi

    void retranslateUi(QDialog *CombatDialog)
    {
        CombatDialog->setWindowTitle(QApplication::translate("CombatDialog", "Combat", 0));
        myCharacter->setText(QString());
        enemyCharacter->setText(QString());
        versusImage->setText(QString());
        submitButton->setText(QApplication::translate("CombatDialog", "Submit Encounter Decisions", 0));
        encounter_runGroupBox->setTitle(QApplication::translate("CombatDialog", "Run Away?", 0));
        yesRun->setText(QApplication::translate("CombatDialog", "Yes", 0));
        noRun->setText(QApplication::translate("CombatDialog", "No", 0));
        moveGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Move Counter", 0));
        melee_fightGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Fight Counter", 0));
        melee_moveTypeGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Combat Move", 0));

        const bool __sortingEnabled = moveTypeList->isSortingEnabled();
        moveTypeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = moveTypeList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("CombatDialog", "Charge", 0));
        QListWidgetItem *___qlistwidgetitem1 = moveTypeList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("CombatDialog", "Dodge", 0));
        QListWidgetItem *___qlistwidgetitem2 = moveTypeList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("CombatDialog", "Duck", 0));
        moveTypeList->setSortingEnabled(__sortingEnabled);

        melee_blockTypeGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Shield Block", 0));

        const bool __sortingEnabled1 = blockTypeList->isSortingEnabled();
        blockTypeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem3 = blockTypeList->item(0);
        ___qlistwidgetitem3->setText(QApplication::translate("CombatDialog", "Thrust", 0));
        QListWidgetItem *___qlistwidgetitem4 = blockTypeList->item(1);
        ___qlistwidgetitem4->setText(QApplication::translate("CombatDialog", "Swing", 0));
        QListWidgetItem *___qlistwidgetitem5 = blockTypeList->item(2);
        ___qlistwidgetitem5->setText(QApplication::translate("CombatDialog", "Smash", 0));
        blockTypeList->setSortingEnabled(__sortingEnabled1);

        melee_fightTypeGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Fight Move", 0));

        const bool __sortingEnabled2 = fightTypeList->isSortingEnabled();
        fightTypeList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem6 = fightTypeList->item(0);
        ___qlistwidgetitem6->setText(QApplication::translate("CombatDialog", "Thrust", 0));
        QListWidgetItem *___qlistwidgetitem7 = fightTypeList->item(1);
        ___qlistwidgetitem7->setText(QApplication::translate("CombatDialog", "Swing", 0));
        QListWidgetItem *___qlistwidgetitem8 = fightTypeList->item(2);
        ___qlistwidgetitem8->setText(QApplication::translate("CombatDialog", "Smash", 0));
        fightTypeList->setSortingEnabled(__sortingEnabled2);

    } // retranslateUi

};

namespace Ui {
    class CombatDialog: public Ui_CombatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBATDIALOG_H
