#ifndef DEPENDENCYWIDGET_H
#define DEPENDENCYWIDGET_H

#include <QDialog>
#include <QTextBrowser>
#include <QList>
#include <QLabel>

class DependencyWidget : public QDialog
{
  public:
    DependencyWidget(QWidget *parent = 0);

    void setPkgs(QList<QString> *pkgsInstall, QList<QString> *pkgsRemove);
    void clear();
    
  private:
    QTextBrowser *m_dependencyList;
    QLabel *m_headerLabel; 
};

#endif //DEPENDENCYWIDGET_H
