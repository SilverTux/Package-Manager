/********************************************************************************
** Form generated from reading UI file 'DebconfMultiselect.ui'
**
** Created: Wed Nov 9 00:49:48 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFMULTISELECT_H
#define UI_DEBCONFMULTISELECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfMultiselect
{
public:
    QGridLayout *gridLayout;
    QLabel *descriptionL;
    QListView *multiselectLV;
    QLabel *extendedDescriptionL;

    void setupUi(QWidget *DebconfMultiselect)
    {
        if (DebconfMultiselect->objectName().isEmpty())
            DebconfMultiselect->setObjectName(QString::fromUtf8("DebconfMultiselect"));
        DebconfMultiselect->resize(400, 217);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfMultiselect->sizePolicy().hasHeightForWidth());
        DebconfMultiselect->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfMultiselect);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        descriptionL = new QLabel(DebconfMultiselect);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        descriptionL->setFont(font);
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 0, 0, 1, 1);

        multiselectLV = new QListView(DebconfMultiselect);
        multiselectLV->setObjectName(QString::fromUtf8("multiselectLV"));
        multiselectLV->setEditTriggers(QAbstractItemView::NoEditTriggers);
        multiselectLV->setProperty("showDropIndicator", QVariant(false));
        multiselectLV->setSelectionMode(QAbstractItemView::NoSelection);

        gridLayout->addWidget(multiselectLV, 2, 0, 1, 1);

        extendedDescriptionL = new QLabel(DebconfMultiselect);
        extendedDescriptionL->setObjectName(QString::fromUtf8("extendedDescriptionL"));
        extendedDescriptionL->setWordWrap(true);
        extendedDescriptionL->setIndent(10);

        gridLayout->addWidget(extendedDescriptionL, 1, 0, 1, 1);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(multiselectLV);
        extendedDescriptionL->setBuddy(multiselectLV);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfMultiselect);

        QMetaObject::connectSlotsByName(DebconfMultiselect);
    } // setupUi

    void retranslateUi(QWidget *DebconfMultiselect)
    {
        descriptionL->setText(QApplication::translate("DebconfMultiselect", "TextLabel", 0, QApplication::UnicodeUTF8));
        extendedDescriptionL->setText(QApplication::translate("DebconfMultiselect", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DebconfMultiselect);
    } // retranslateUi

};

namespace Ui {
    class DebconfMultiselect: public Ui_DebconfMultiselect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFMULTISELECT_H
