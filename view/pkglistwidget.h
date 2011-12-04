#ifndef PKGLISTWIDGET_H
#define PKGLISTWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QList>
#include <QPoint>
#include <QModelIndex>

class pkgListWidget : public QTableView
{
  Q_OBJECT

  public:
    pkgListWidget(QWidget *parent = 0);
    ~pkgListWidget();

  public Q_SLOTS:
    void rowClicked(const QModelIndex &index);
    void rowDoubleClicked(const QModelIndex &index);
    void rightClickedCell(QPoint point);
    void selectedForInstall();
    void selectedForRemove();

  Q_SIGNALS:
    void clickedRow(QString pkgName);
    void doubleClickedRow(QString pkgName);
    void propertyClicked();
    void installClicked(QString pkgName);
    void removeClicked(QString pkgName);

  private:
    QModelIndex index;
};

#endif //PKGLISTWIDGET_H
