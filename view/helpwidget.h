#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QTextBrowser>

class HelpWidget : public QWidget
{
    Q_OBJECT
public:
    HelpWidget();

public slots:
    void loadAndShow();

private:
    void setupUi();
    void loadHelpFile(const QString filename);

    QTextBrowser *m_textBrowser;
};

#endif // HELPWIDGET_H
