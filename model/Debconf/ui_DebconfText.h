/********************************************************************************
** Form generated from reading UI file 'DebconfText.ui'
**
** Created: Wed Nov 9 01:16:43 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFTEXT_H
#define UI_DEBCONFTEXT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfText
{
public:
    QVBoxLayout *verticalLayout;
    QTextEdit *textTE;

    void setupUi(QWidget *DebconfText)
    {
        if (DebconfText->objectName().isEmpty())
            DebconfText->setObjectName(QString::fromUtf8("DebconfText"));
        DebconfText->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfText->sizePolicy().hasHeightForWidth());
        DebconfText->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(DebconfText);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textTE = new QTextEdit(DebconfText);
        textTE->setObjectName(QString::fromUtf8("textTE"));
        textTE->setAutoFormatting(QTextEdit::AutoAll);
        textTE->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(textTE);


        retranslateUi(DebconfText);

        QMetaObject::connectSlotsByName(DebconfText);
    } // setupUi

    void retranslateUi(QWidget *DebconfText)
    {
        DebconfText->setWindowTitle(QApplication::translate("DebconfText", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfText: public Ui_DebconfText {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFTEXT_H
