#include "cacheupdatewidget.h"

#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QStandardItemModel>

#include <QIcon>
#include <QLocale>
#include <QDebug>

#include <libqapt/globals.h>

CacheUpdateWidget::CacheUpdateWidget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    m_headerLabel = new QLabel();

    m_downloadView = new QListView();

    m_downloadModel = new QStandardItemModel(this);
    m_downloadView->setModel(m_downloadModel);

    m_downloadLabel = new QLabel();
    m_totalProgress = new QProgressBar();

    m_cancelButton = new QPushButton();
    m_cancelButton->setText(trUtf8("Mégse"));

    setWindowTitle(trUtf8("Letöltés"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));

    layout->addWidget(m_headerLabel);
    layout->addWidget(m_downloadView);
    layout->addWidget(m_downloadLabel);
    layout->addWidget(m_totalProgress);
    layout->addWidget(m_cancelButton);

    setLayout(layout);
}

CacheUpdateWidget::~CacheUpdateWidget()
{
}

void CacheUpdateWidget::clear()
{
    m_downloadModel->clear();
    m_totalProgress->setValue(0);
}

void CacheUpdateWidget::setHeaderText(const QString &text)
{
    m_headerLabel->setText(text);
}

void CacheUpdateWidget::addItem(const QString &message)
{
    QStandardItem *n = new QStandardItem();
    n->setText(message);
    m_downloadModel->appendRow(n);
    m_downloadView->scrollTo(m_downloadModel->indexFromItem(n));
}

void CacheUpdateWidget::updateDownloadProgress(int percentage, int speed, int ETA)
{
    m_totalProgress->setValue(percentage);

    QString downloadSpeed;
    if (speed < 0) {
        downloadSpeed = trUtf8("Ismeretlen sebesség");
    } else {
        downloadSpeed = trUtf8("Letöltési sebesség: %1/s").arg(speed);
    }

    QString timeRemaining;
    int ETAMilliseconds = ETA * 1000;

    if (ETAMilliseconds <= 0 || ETAMilliseconds > 14*24*60*60) {
        // If ETA is less than zero or bigger than 2 weeks
        timeRemaining = trUtf8(" - Hátralévő idő ismeretlen");
    } else {
        timeRemaining = QString(" - %1/s").arg(ETA);
    }
    m_downloadLabel->setText(downloadSpeed + timeRemaining);
}

void CacheUpdateWidget::updateDownloadMessage(int flag, const QString &message)
{
    QString fullMessage;

    switch (flag) {
      case QApt::DownloadFetch:
          fullMessage = QString("Letöltés: %1").arg(message);
          break;
      case QApt::HitFetch:
          fullMessage = QString("Ellenőrzés: %1").arg(message);
          break;
      case QApt::IgnoredFetch:
          fullMessage = QString("Elvet: %1").arg(message);
          break;
      default:
          fullMessage = message;
    }
    addItem(fullMessage);
}

void CacheUpdateWidget::cancelButtonPressed()
{
    Q_EMIT(cancelCacheUpdate());
}

