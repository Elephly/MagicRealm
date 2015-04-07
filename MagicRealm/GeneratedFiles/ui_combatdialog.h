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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CombatDialog
{
public:
    QLabel *myCharacter;
    QLabel *enemyCharacter;
    QLabel *versusImage;

    void setupUi(QDialog *CombatDialog)
    {
        if (CombatDialog->objectName().isEmpty())
            CombatDialog->setObjectName(QStringLiteral("CombatDialog"));
        CombatDialog->resize(800, 600);
        myCharacter = new QLabel(CombatDialog);
        myCharacter->setObjectName(QStringLiteral("myCharacter"));
        myCharacter->setGeometry(QRect(0, 0, 380, 600));
        enemyCharacter = new QLabel(CombatDialog);
        enemyCharacter->setObjectName(QStringLiteral("enemyCharacter"));
        enemyCharacter->setGeometry(QRect(420, 0, 380, 600));
        versusImage = new QLabel(CombatDialog);
        versusImage->setObjectName(QStringLiteral("versusImage"));
        versusImage->setGeometry(QRect(380, 275, 40, 53));
        versusImage->setPixmap(QPixmap(QString::fromUtf8(":/images/combat/versus.png")));
        versusImage->setScaledContents(true);

        retranslateUi(CombatDialog);

        QMetaObject::connectSlotsByName(CombatDialog);
    } // setupUi

    void retranslateUi(QDialog *CombatDialog)
    {
        CombatDialog->setWindowTitle(QApplication::translate("CombatDialog", "Combat", 0));
        myCharacter->setText(QString());
        enemyCharacter->setText(QString());
        versusImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CombatDialog: public Ui_CombatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBATDIALOG_H
