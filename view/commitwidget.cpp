#include "commitwidget.h"

//Qt
#include <QLabel>
#include <QProgressBar>

CommitWidget::CommitWidget(QWidget *parent)
    : QWidget(parent)
{
    m_commitBrowser = new QTextBrowser();
    m_progressBar = new QProgressBar();

    QVBoxLayout* vl = new QVBoxLayout();

    vl->addWidget(m_commitBrowser);
    vl->addWidget(m_progressBar);

    setLayout(vl);
    setWindowTitle(trUtf8("Csomagok telepítése"));
}

CommitWidget::~CommitWidget()
{
}

void CommitWidget::setLabelText(const QString &text)
{
    m_commitBrowser->setText(m_commitBrowser->toPlainText() + "\n" + text);
}

void CommitWidget::setProgress(int percentage)
{
    m_progressBar->setValue(percentage);
}

void CommitWidget::clear()
{
    m_commitBrowser->setText(QString());
    m_progressBar->setValue(0);
}
