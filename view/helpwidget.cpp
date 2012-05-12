#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

#include "helpwidget.h"

HelpWidget::HelpWidget()
{
    setupUi();
}

void HelpWidget::loadAndShow()
{
    loadHelpFile("help.html");
    show();
}

void HelpWidget::setupUi()
{
    QPushButton *okBtn = new QPushButton("Ok");
    QVBoxLayout *layout = new QVBoxLayout();
    m_textBrowser = new QTextBrowser();
    m_textBrowser->setOpenLinks(false);

    layout->addWidget(m_textBrowser);
    layout->addWidget(okBtn);

    setLayout(layout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(close()));
    connect(m_textBrowser, SIGNAL(anchorClicked(QUrl)),
            m_textBrowser, SLOT(setSource(QUrl)));

    setWindowTitle(trUtf8("Súgó"));
    setMinimumWidth(500);
}

void HelpWidget::loadHelpFile(const QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString wTitle = trUtf8("Hiba!");
        QString wMessage = trUtf8("Hiba a súgófájl betöltése közben!");
        QMessageBox::warning(this, wTitle, wMessage);
        return;
    }

    QString source;

    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        QString temp(line);

        source += trUtf8(temp.toStdString().c_str());
    }

    m_textBrowser->setHtml(source);

    file.close();
}


