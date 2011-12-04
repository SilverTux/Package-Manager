/********************************************************************************
** Form generated from reading UI file 'DebconfNote.ui'
**
** Created: Wed Nov 9 01:16:43 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFNOTE_H
#define UI_DEBCONFNOTE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfNote
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *descriptionL;
    QTextEdit *noteTE;

    void setupUi(QWidget *DebconfNote)
    {
        if (DebconfNote->objectName().isEmpty())
            DebconfNote->setObjectName(QString::fromUtf8("DebconfNote"));
        DebconfNote->resize(400, 319);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfNote->sizePolicy().hasHeightForWidth());
        DebconfNote->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(DebconfNote);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        descriptionL = new QLabel(DebconfNote);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        descriptionL->setWordWrap(true);

        verticalLayout->addWidget(descriptionL);

        noteTE = new QTextEdit(DebconfNote);
        noteTE->setObjectName(QString::fromUtf8("noteTE"));
        noteTE->setAutoFormatting(QTextEdit::AutoAll);
        noteTE->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout->addWidget(noteTE);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(noteTE);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfNote);

        QMetaObject::connectSlotsByName(DebconfNote);
    } // setupUi

    void retranslateUi(QWidget *DebconfNote)
    {
        DebconfNote->setWindowTitle(QApplication::translate("DebconfNote", "Form", 0, QApplication::UnicodeUTF8));
        descriptionL->setText(QApplication::translate("DebconfNote", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfNote: public Ui_DebconfNote {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFNOTE_H
