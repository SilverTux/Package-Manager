/********************************************************************************
** Form generated from reading UI file 'DebconfError.ui'
**
** Created: Wed Nov 9 00:49:48 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFERROR_H
#define UI_DEBCONFERROR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfError
{
public:
    QGridLayout *gridLayout;
    QLabel *iconL;
    QTextEdit *textTE;
    QLabel *descriptionL;

    void setupUi(QWidget *DebconfError)
    {
        if (DebconfError->objectName().isEmpty())
            DebconfError->setObjectName(QString::fromUtf8("DebconfError"));
        DebconfError->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfError->sizePolicy().hasHeightForWidth());
        DebconfError->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfError);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        iconL = new QLabel(DebconfError);
        iconL->setObjectName(QString::fromUtf8("iconL"));

        gridLayout->addWidget(iconL, 0, 0, 2, 1);

        textTE = new QTextEdit(DebconfError);
        textTE->setObjectName(QString::fromUtf8("textTE"));
        textTE->setUndoRedoEnabled(false);
        textTE->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(textTE, 1, 2, 1, 1);

        descriptionL = new QLabel(DebconfError);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 0, 2, 1, 1);

#ifndef QT_NO_SHORTCUT
        iconL->setBuddy(textTE);
        descriptionL->setBuddy(textTE);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfError);

        QMetaObject::connectSlotsByName(DebconfError);
    } // setupUi

    void retranslateUi(QWidget *DebconfError)
    {
        DebconfError->setWindowTitle(QApplication::translate("DebconfError", "Form", 0, QApplication::UnicodeUTF8));
        iconL->setText(QApplication::translate("DebconfError", "Icon", 0, QApplication::UnicodeUTF8));
        descriptionL->setText(QApplication::translate("DebconfError", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfError: public Ui_DebconfError {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFERROR_H
