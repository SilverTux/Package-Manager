/********************************************************************************
** Form generated from reading UI file 'DebconfProgress.ui'
**
** Created: Wed Nov 9 00:49:49 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBCONFPROGRESS_H
#define UI_DEBCONFPROGRESS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebconfProgress
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QProgressBar *progressBar;

    void setupUi(QWidget *DebconfProgress)
    {
        if (DebconfProgress->objectName().isEmpty())
            DebconfProgress->setObjectName(QString::fromUtf8("DebconfProgress"));
        DebconfProgress->resize(294, 46);
        verticalLayout = new QVBoxLayout(DebconfProgress);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(DebconfProgress);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        progressBar = new QProgressBar(DebconfProgress);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setMaximum(0);

        verticalLayout->addWidget(progressBar);


        retranslateUi(DebconfProgress);

        QMetaObject::connectSlotsByName(DebconfProgress);
    } // setupUi

    void retranslateUi(QWidget *DebconfProgress)
    {
        DebconfProgress->setWindowTitle(QApplication::translate("DebconfProgress", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DebconfProgress", "Label", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DebconfProgress: public Ui_DebconfProgress {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBCONFPROGRESS_H
