/********************************************************************************
** Form generated from reading UI file 'DebconfString.ui'
**
** Created: Wed Nov 9 01:16:43 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFSTRING_H
#define UI_DEBCONFSTRING_H

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

class Ui_DebconfString
{
public:
    QGridLayout *gridLayout;
    QLabel *descriptionL;
    QLineEdit *stringLE;
    QLabel *extendedDescriptionL;

    void setupUi(QWidget *DebconfString)
    {
        if (DebconfString->objectName().isEmpty())
            DebconfString->setObjectName(QString::fromUtf8("DebconfString"));
        DebconfString->resize(400, 66);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfString->sizePolicy().hasHeightForWidth());
        DebconfString->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfString);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        descriptionL = new QLabel(DebconfString);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        descriptionL->setFont(font);
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 0, 0, 1, 1);

        stringLE = new QLineEdit(DebconfString);
        stringLE->setObjectName(QString::fromUtf8("stringLE"));
        stringLE->setProperty("showClearButton", QVariant(true));

        gridLayout->addWidget(stringLE, 2, 0, 1, 1);

        extendedDescriptionL = new QLabel(DebconfString);
        extendedDescriptionL->setObjectName(QString::fromUtf8("extendedDescriptionL"));
        extendedDescriptionL->setWordWrap(true);
        extendedDescriptionL->setIndent(10);

        gridLayout->addWidget(extendedDescriptionL, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(stringLE);
        extendedDescriptionL->setBuddy(stringLE);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfString);

        QMetaObject::connectSlotsByName(DebconfString);
    } // setupUi

    void retranslateUi(QWidget *DebconfString)
    {
        DebconfString->setWindowTitle(QApplication::translate("DebconfString", "Form", 0, QApplication::UnicodeUTF8));
        descriptionL->setText(QApplication::translate("DebconfString", "TextLabel", 0, QApplication::UnicodeUTF8));
        extendedDescriptionL->setText(QApplication::translate("DebconfString", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfString: public Ui_DebconfString {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFSTRING_H
