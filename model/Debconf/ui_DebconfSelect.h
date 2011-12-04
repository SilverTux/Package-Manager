/********************************************************************************
** Form generated from reading UI file 'DebconfSelect.ui'
**
** Created: Wed Nov 9 01:16:43 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFSELECT_H
#define UI_DEBCONFSELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfSelect
{
public:
    QGridLayout *gridLayout;
    QLabel *descriptionL;
    QComboBox *selectCB;
    QLabel *extendedDescriptionL;

    void setupUi(QWidget *DebconfSelect)
    {
        if (DebconfSelect->objectName().isEmpty())
            DebconfSelect->setObjectName(QString::fromUtf8("DebconfSelect"));
        DebconfSelect->resize(404, 66);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfSelect->sizePolicy().hasHeightForWidth());
        DebconfSelect->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfSelect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        descriptionL = new QLabel(DebconfSelect);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        descriptionL->setFont(font);
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 0, 0, 1, 1);

        selectCB = new QComboBox(DebconfSelect);
        selectCB->setObjectName(QString::fromUtf8("selectCB"));

        gridLayout->addWidget(selectCB, 2, 0, 1, 1);

        extendedDescriptionL = new QLabel(DebconfSelect);
        extendedDescriptionL->setObjectName(QString::fromUtf8("extendedDescriptionL"));
        extendedDescriptionL->setWordWrap(true);
        extendedDescriptionL->setIndent(10);

        gridLayout->addWidget(extendedDescriptionL, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(selectCB);
        extendedDescriptionL->setBuddy(selectCB);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfSelect);

        QMetaObject::connectSlotsByName(DebconfSelect);
    } // setupUi

    void retranslateUi(QWidget *DebconfSelect)
    {
        DebconfSelect->setWindowTitle(QApplication::translate("DebconfSelect", "Form", 0, QApplication::UnicodeUTF8));
        descriptionL->setText(QApplication::translate("DebconfSelect", "TextLabel", 0, QApplication::UnicodeUTF8));
        extendedDescriptionL->setText(QApplication::translate("DebconfSelect", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfSelect: public Ui_DebconfSelect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFSELECT_H
