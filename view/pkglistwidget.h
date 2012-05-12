#ifndef PKGLISTWIDGET_H
#define PKGLISTWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QList>
#include <QPoint>
#include <QModelIndex>

class PkgListWidget : public QTableView
{
  Q_OBJECT

  public:
    PkgListWidget(QWidget *parent = 0);
    ~PkgListWidget();

  public Q_SLOTS:
    void rowClicked(const QModelIndex &index);
    void rowDoubleClicked(const QModelIndex &index);
    void rightClickedCell(QPoint point);
    void undoSelection();
    void selectedForInstall();
    void selectedForRemove();

  Q_SIGNALS:
    void clickedRow(QString pkgName);
    void doubleClickedRow(QString pkgName);
    void propertyClicked();
    void undoClicked(QString pkgName);
    void installClicked(QString pkgName);
    void removeClicked(QString pkgName);

  private:
    QModelIndex m_index;
};

#endif //PKGLISTWIDGET_H
