/********************************************************************************
** Form generated from reading UI file 'DebconfGui.ui'
**
** Created: Wed Nov 9 01:16:43 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFGUI_H
#define UI_DEBCONFGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfGui
{
public:
    QGridLayout *gridLayout;
    QLabel *titleL;
    QLabel *iconL;
    QFrame *line;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelPB;
    QPushButton *backPB;
    QPushButton *nextPB;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *DebconfGui)
    {
        if (DebconfGui->objectName().isEmpty())
            DebconfGui->setObjectName(QString::fromUtf8("DebconfGui"));
        DebconfGui->resize(448, 293);
        gridLayout = new QGridLayout(DebconfGui);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        titleL = new QLabel(DebconfGui);
        titleL->setObjectName(QString::fromUtf8("titleL"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(titleL->sizePolicy().hasHeightForWidth());
        titleL->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        titleL->setFont(font);
        titleL->setText(QString::fromUtf8("Question Title"));
        titleL->setWordWrap(true);

        gridLayout->addWidget(titleL, 0, 1, 1, 2);

        iconL = new QLabel(DebconfGui);
        iconL->setObjectName(QString::fromUtf8("iconL"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(iconL->sizePolicy().hasHeightForWidth());
        iconL->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(iconL, 0, 3, 1, 1);

        line = new QFrame(DebconfGui);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 1, 1, 3);

        line_2 = new QFrame(DebconfGui);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 3, 1, 1, 3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelPB = new QPushButton(DebconfGui);
        cancelPB->setObjectName(QString::fromUtf8("cancelPB"));

        horizontalLayout->addWidget(cancelPB);

        backPB = new QPushButton(DebconfGui);
        backPB->setObjectName(QString::fromUtf8("backPB"));
        backPB->setEnabled(false);

        horizontalLayout->addWidget(backPB);

        nextPB = new QPushButton(DebconfGui);
        nextPB->setObjectName(QString::fromUtf8("nextPB"));
        nextPB->setAutoDefault(true);
        nextPB->setDefault(true);

        horizontalLayout->addWidget(nextPB);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 3);

        scrollArea = new QScrollArea(DebconfGui);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 440, 222));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 2, 1, 1, 3);

        QWidget::setTabOrder(nextPB, backPB);
        QWidget::setTabOrder(backPB, cancelPB);

        retranslateUi(DebconfGui);
        QObject::connect(nextPB, SIGNAL(clicked(bool)), nextPB, SLOT(setEnabled(bool)));
        QObject::connect(nextPB, SIGNAL(clicked(bool)), backPB, SLOT(setEnabled(bool)));
        QObject::connect(backPB, SIGNAL(clicked(bool)), nextPB, SLOT(setEnabled(bool)));
        QObject::connect(backPB, SIGNAL(clicked(bool)), backPB, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(DebconfGui);
    } // setupUi

    void retranslateUi(QWidget *DebconfGui)
    {
        DebconfGui->setWindowTitle(QApplication::translate("DebconfGui", "Form", 0, QApplication::UnicodeUTF8));
        iconL->setText(QApplication::translate("DebconfGui", "Icon", 0, QApplication::UnicodeUTF8));
        cancelPB->setText(QApplication::translate("DebconfGui", "Cancel", 0, QApplication::UnicodeUTF8));
        backPB->setText(QApplication::translate("DebconfGui", "Back", 0, QApplication::UnicodeUTF8));
        nextPB->setText(QApplication::translate("DebconfGui", "Continue", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfGui: public Ui_DebconfGui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFGUI_H
