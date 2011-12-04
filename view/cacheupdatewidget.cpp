#include "cacheupdatewidget.h"

#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QStandardItemModel>

#include <QIcon>
#include <QLocale>
#include <QDebug>

CacheUpdateWidget::CacheUpdateWidget(QWidget *parent)
    : QWidget(parent)
{
    m_headerLabel = new QLabel();

    m_downloadView = new QListView();

    m_downloadModel = new QStandardItemModel(this);
    m_downloadView->setModel(m_downloadModel);

    m_downloadLabel = new QLabel();
    m_totalProgress = new QProgressBar();

    m_cancelButton = new QPushButton();
    m_cancelButton->setText(trUtf8("Mégse"));
    m_cancelButton->setIcon(QIcon(""));

    setWindowTitle(trUtf8("Cache Update"));
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPressed()));
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

void CacheUpdateWidget::setTotalProgress(int percentage, int speed, int ETA)
{
    m_totalProgress->setValue(percentage);

    QString downloadSpeed;
    if (speed < 0) {
        downloadSpeed = trUtf8("Ismeretlen sebesség");
    } else {
        downloadSpeed = trUtf8("Letöltési sebesség: %1/s");
    }

    QString timeRemaining;
    int ETAMilliseconds = ETA * 1000;

    if (ETAMilliseconds <= 0 || ETAMilliseconds > 14*24*60*60) {
        // If ETA is less than zero or bigger than 2 weeks
        timeRemaining = trUtf8(" - Hátralévő idő ismeretlen");
    } else {
        timeRemaining = " - %1/s";
    }
    m_downloadLabel->setText(downloadSpeed + timeRemaining);
}

void CacheUpdateWidget::cancelButtonPressed()
{
    Q_EMIT(cancelCacheUpdate());
}

