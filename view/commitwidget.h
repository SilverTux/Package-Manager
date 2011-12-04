#ifndef COMMITWIDGET_H
#define COMMITWIDGET_H

#include <QVBoxLayout>
#include <QWidget>
#include <QTextBrowser>

class QLabel;
class QProgressBar;

class CommitWidget : public QWidget
{
    Q_OBJECT
public:
    CommitWidget(QWidget *parent = 0);
    ~CommitWidget();

    void setLabelText(const QString &text);
    void setProgress(int percentage);
    void clear();

private:
    QTextBrowser *m_commitBrowser;
    QProgressBar *m_progressBar;
};

#endif
