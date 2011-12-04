/********************************************************************************
** Form generated from reading UI file 'DebconfBoolean.ui'
**
** Created: Wed Nov 9 00:49:48 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFBOOLEAN_H
#define UI_DEBCONFBOOLEAN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfBoolean
{
public:
    QGridLayout *gridLayout;
    QLabel *descriptionL;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer;
    QLabel *extendedDescriptionL;

    void setupUi(QWidget *DebconfBoolean)
    {
        if (DebconfBoolean->objectName().isEmpty())
            DebconfBoolean->setObjectName(QString::fromUtf8("DebconfBoolean"));
        DebconfBoolean->resize(400, 63);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DebconfBoolean->sizePolicy().hasHeightForWidth());
        DebconfBoolean->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(DebconfBoolean);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        descriptionL = new QLabel(DebconfBoolean);
        descriptionL->setObjectName(QString::fromUtf8("descriptionL"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        descriptionL->setFont(font);
        descriptionL->setWordWrap(true);

        gridLayout->addWidget(descriptionL, 3, 0, 1, 3);

        radioButton = new QRadioButton(DebconfBoolean);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy1);
        radioButton->setChecked(true);

        gridLayout->addWidget(radioButton, 5, 0, 1, 1);

        radioButton_2 = new QRadioButton(DebconfBoolean);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        sizePolicy1.setHeightForWidth(radioButton_2->sizePolicy().hasHeightForWidth());
        radioButton_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(radioButton_2, 5, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 2, 1, 1);

        extendedDescriptionL = new QLabel(DebconfBoolean);
        extendedDescriptionL->setObjectName(QString::fromUtf8("extendedDescriptionL"));
        extendedDescriptionL->setWordWrap(true);
        extendedDescriptionL->setIndent(10);

        gridLayout->addWidget(extendedDescriptionL, 4, 0, 1, 3);

#ifndef QT_NO_SHORTCUT
        descriptionL->setBuddy(radioButton);
        extendedDescriptionL->setBuddy(radioButton);
#endif // QT_NO_SHORTCUT

        retranslateUi(DebconfBoolean);

        QMetaObject::connectSlotsByName(DebconfBoolean);
    } // setupUi

    void retranslateUi(QWidget *DebconfBoolean)
    {
        DebconfBoolean->setWindowTitle(QApplication::translate("DebconfBoolean", "Form", 0, QApplication::UnicodeUTF8));
        descriptionL->setText(QApplication::translate("DebconfBoolean", "TextLabel", 0, QApplication::UnicodeUTF8));
        radioButton->setText(QApplication::translate("DebconfBoolean", "Yes", 0, QApplication::UnicodeUTF8));
        radioButton_2->setText(QApplication::translate("DebconfBoolean", "No", 0, QApplication::UnicodeUTF8));
        extendedDescriptionL->setText(QApplication::translate("DebconfBoolean", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfBoolean: public Ui_DebconfBoolean {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFBOOLEAN_H
