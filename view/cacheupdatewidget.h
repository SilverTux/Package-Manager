#ifndef CACHEUPDATEWIDGET_H
#define CACHEUPDATEWIDGET_H

#include <QItemDelegate>
#include <QTextDocument>
#include <QWidget>

#include <QVBoxLayout>

class QLabel;
class QListView;
class QProgressBar;
class QStandardItemModel;
class QPushButton;

class CacheUpdateWidget : public QWidget
{
    Q_OBJECT
public:
    CacheUpdateWidget(QWidget *parent=0);

    ~CacheUpdateWidget();

public Q_SLOTS:
    void clear();
    void addItem(const QString &message);
    void updateDownloadProgress(int percentage, int speed, int ETA);
    void updateDownloadMessage(int flag, const QString &message);
    void setHeaderText(const QString &text);

private:
    QLabel *m_headerLabel;
    QListView *m_downloadView;
    QStandardItemModel *m_downloadModel;
    QProgressBar *m_totalProgress;
    QLabel *m_downloadLabel;
    QPushButton *m_cancelButton;

private Q_SLOTS:
    void cancelButtonPressed();

Q_SIGNALS:
    void cancelCacheUpdate();
};

#endif
