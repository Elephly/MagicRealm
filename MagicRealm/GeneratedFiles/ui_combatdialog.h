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
    QGroupBox *runGroupBox;
    QVBoxLayout *verticalLayout;
    QRadioButton *yesRun;
    QRadioButton *noRun;
    QGroupBox *moveGroupBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *moveCounterList;

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
        submitButton->setEnabled(false);
        submitButton->setGeometry(QRect(270, 500, 260, 60));
        QFont font;
        font.setFamily(QStringLiteral("MS Serif"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        submitButton->setFont(font);
        submitButton->setDefault(false);
        runGroupBox = new QGroupBox(CombatDialog);
        runGroupBox->setObjectName(QStringLiteral("runGroupBox"));
        runGroupBox->setGeometry(QRect(340, 380, 120, 80));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Serif"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        runGroupBox->setFont(font1);
        runGroupBox->setStyleSheet(QStringLiteral("background-color : white;"));
        runGroupBox->setAlignment(Qt::AlignCenter);
        verticalLayout = new QVBoxLayout(runGroupBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        yesRun = new QRadioButton(runGroupBox);
        yesRun->setObjectName(QStringLiteral("yesRun"));
        yesRun->setLayoutDirection(Qt::LeftToRight);

        verticalLayout->addWidget(yesRun);

        noRun = new QRadioButton(runGroupBox);
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


        retranslateUi(CombatDialog);

        QMetaObject::connectSlotsByName(CombatDialog);
    } // setupUi

    void retranslateUi(QDialog *CombatDialog)
    {
        CombatDialog->setWindowTitle(QApplication::translate("CombatDialog", "Combat", 0));
        myCharacter->setText(QString());
        enemyCharacter->setText(QString());
        versusImage->setText(QString());
        submitButton->setText(QApplication::translate("CombatDialog", "Submit Encounter Decisions", 0));
        runGroupBox->setTitle(QApplication::translate("CombatDialog", "Run Away?", 0));
        yesRun->setText(QApplication::translate("CombatDialog", "Yes", 0));
        noRun->setText(QApplication::translate("CombatDialog", "No", 0));
        moveGroupBox->setTitle(QApplication::translate("CombatDialog", "Select Move Counter", 0));
    } // retranslateUi

};

namespace Ui {
    class CombatDialog: public Ui_CombatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBATDIALOG_H
