/********************************************************************************
** Form generated from reading UI file 'DebconfPassword.ui'
**
** Created: Wed Nov 9 01:22:42 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFPASSWORD_H
#define UI_DEBCONFPASSWORD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfPassword
{
public:
    QGridLayout *gridLayout;
    QLabel *descriptionL;
    QLineEdit *passwordLE;
    QLabel *extendedDescriptionL;

    void setupUi(QWidget *DebconfPassword)
    {
        if (DebconfPassword->objectName().isEmpty())
            DebconfPassword->setObjectName(QString::fromUtf8("DebconfPassword"));
        DebconfPassword->resize(400, 66);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfPassword->sizePolicy().hasHeightForWidth());
        DebconfPassword->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfPassword);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        descriptionL = new QLabel(DebconfPassword);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        descriptionL->setFont(font);
        descriptionL->setText(QString::fromUtf8("Description"));
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 0, 0, 1, 1);

        passwordLE = new QLineEdit(DebconfPassword);
        passwordLE->setObjectName(QString::fromUtf8("passwordLE"));
        passwordLE->setEchoMode(QLineEdit::Password);
        passwordLE->setProperty("showClearButton", QVariant(true));

        gridLayout->addWidget(passwordLE, 2, 0, 1, 1);

        extendedDescriptionL = new QLabel(DebconfPassword);
        extendedDescriptionL->setObjectName(QString::fromUtf8("extendedDescriptionL"));
        extendedDescriptionL->setWordWrap(true);
        extendedDescriptionL->setIndent(10);

        gridLayout->addWidget(extendedDescriptionL, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(passwordLE);
        extendedDescriptionL->setBuddy(passwordLE);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfPassword);

        QMetaObject::connectSlotsByName(DebconfPassword);
    } // setupUi

    void retranslateUi(QWidget *DebconfPassword)
    {
        DebconfPassword->setWindowTitle(QApplication::translate("DebconfPassword", "Form", 0, QApplication::UnicodeUTF8));
        extendedDescriptionL->setText(QApplication::translate("DebconfPassword", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfPassword: public Ui_DebconfPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFPASSWORD_H
