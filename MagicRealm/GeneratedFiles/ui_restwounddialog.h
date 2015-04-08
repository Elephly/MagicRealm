/********************************************************************************
** Form generated from reading UI file 'restwounddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESTWOUNDDIALOG_H
#define UI_RESTWOUNDDIALOG_H

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

QT_BEGIN_NAMESPACE

class Ui_RestWoundDialog
{
public:
    QLabel *myCharacter;
    QGroupBox *counterGroupBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *counterList;
    QPushButton *submitButton;

    void setupUi(QDialog *RestWoundDialog)
    {
        if (RestWoundDialog->objectName().isEmpty())
            RestWoundDialog->setObjectName(QStringLiteral("RestWoundDialog"));
        RestWoundDialog->resize(380, 325);
        myCharacter = new QLabel(RestWoundDialog);
        myCharacter->setObjectName(QStringLiteral("myCharacter"));
        myCharacter->setGeometry(QRect(0, 0, 380, 600));
        myCharacter->setPixmap(QPixmap(QString::fromUtf8(":/images/characterprofile/black_knight.jpg")));
        counterGroupBox = new QGroupBox(RestWoundDialog);
        counterGroupBox->setObjectName(QStringLiteral("counterGroupBox"));
        counterGroupBox->setGeometry(QRect(50, 60, 280, 200));
        QFont font;
        font.setFamily(QStringLiteral("MS Serif"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        counterGroupBox->setFont(font);
        counterGroupBox->setStyleSheet(QStringLiteral("background-color : white"));
        counterGroupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(counterGroupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        counterList = new QListWidget(counterGroupBox);
        counterList->setObjectName(QStringLiteral("counterList"));
        QFont font1;
        font1.setFamily(QStringLiteral("MS Serif"));
        font1.setPointSize(12);
        counterList->setFont(font1);

        horizontalLayout->addWidget(counterList);

        submitButton = new QPushButton(RestWoundDialog);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setEnabled(true);
        submitButton->setGeometry(QRect(90, 270, 200, 40));
        submitButton->setFont(font);
        submitButton->setDefault(false);

        retranslateUi(RestWoundDialog);

        QMetaObject::connectSlotsByName(RestWoundDialog);
    } // setupUi

    void retranslateUi(QDialog *RestWoundDialog)
    {
        RestWoundDialog->setWindowTitle(QApplication::translate("RestWoundDialog", "RestWoundDialog", 0));
        myCharacter->setText(QString());
        counterGroupBox->setTitle(QApplication::translate("RestWoundDialog", "Select a Counter", 0));
        submitButton->setText(QApplication::translate("RestWoundDialog", "Heal", 0));
    } // retranslateUi

};

namespace Ui {
    class RestWoundDialog: public Ui_RestWoundDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESTWOUNDDIALOG_H
