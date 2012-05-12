#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
#include <QPushButton>

#include "aboutwidget.h"

AboutWidget::AboutWidget()
{
    setMinimumSize(330,150);
    setMaximumSize(330,150);
    setWindowTitle(trUtf8("Névjegy"));

    QLabel *programName = new QLabel(trUtf8("Csomagkezelő v0.1"));
    QLabel *authorInfo = new QLabel(trUtf8("Készítette: Bodnár István "
                                           "(boiqaai@caesar.elte.hu)"));
    QPushButton *okBtn = new QPushButton("Ok");
    QVBoxLayout *layout = new QVBoxLayout();
    QFont font;

    font.setPointSize(16);
    font.setBold(true);

    programName->setFont(font);
    programName->setAlignment(Qt::AlignHCenter);

    font.setPointSize(8);
    font.setBold(false);

    authorInfo->setFont(font);
    authorInfo->setAlignment(Qt::AlignHCenter);

    layout->addWidget(programName);
    layout->addWidget(authorInfo);
    layout->addWidget(okBtn);

    setLayout(layout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(hide()));
}
