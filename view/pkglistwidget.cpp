#include "pkglistwidget.h"

#include <QModelIndex>
#include <QMenu>
#include <QAction>

pkgListWidget::pkgListWidget(QWidget *parent) : QTableView(parent)
{
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(rowClicked(const QModelIndex&)));
  connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(rowDoubleClicked(const QModelIndex&)));
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightClickedCell(QPoint)));
}

pkgListWidget::~pkgListWidget()
{
}

void pkgListWidget::rowClicked(const QModelIndex &index)
{
  QModelIndex temp = index.model()->index(index.row(),1);

  Q_EMIT clickedRow(temp.model()->data(temp).toString());
}

void pkgListWidget::rowDoubleClicked(const QModelIndex &index)
{
  QModelIndex temp = index.model()->index(index.row(),1);

  Q_EMIT doubleClickedRow(temp.model()->data(temp).toString());
}

void pkgListWidget::rightClickedCell(QPoint point)
{
  index = indexAt(point);

  QPoint globalPos = mapToGlobal(point);
  QModelIndex temp = index.model()->index(index.row(), 0);
  QModelIndex itemp = temp;

  QMenu myMenu;
  QAction *propertyAct = new QAction(trUtf8("Tulajdonságok"), this);
  QAction *selectForInstall = new QAction(trUtf8("Kijelölés telepítésre"), this);
  QAction *selectForRemove = new QAction(trUtf8("Kijelölés eltávolításra"), this);

  if (temp.model()->data(temp).toBool())
      selectForInstall->setEnabled(false);
  else
      selectForRemove->setEnabled(false);

  myMenu.addAction(selectForInstall);
  myMenu.addAction(selectForRemove);
  myMenu.addSeparator();
  myMenu.addAction(propertyAct);

  connect(propertyAct, SIGNAL(triggered()), this, SIGNAL(propertyClicked()));
  connect(selectForInstall, SIGNAL(triggered()), this, SLOT(selectedForInstall()));
  connect(selectForRemove, SIGNAL(triggered()), this, SLOT(selectedForRemove()));

  //Az adott sor második cellája tartalmazza a csomagnevet
  temp = index.model()->index(index.row(), 1);

  Q_EMIT clickedRow(temp.model()->data(temp).toString());

  myMenu.exec(globalPos);
}

void pkgListWidget::selectedForInstall()
{
  //Az adott sor második cellája tartalmazza a csomagnevet
  QModelIndex temp = index.model()->index(index.row(), 1);

  Q_EMIT installClicked(temp.model()->data(temp).toString());
}

void pkgListWidget::selectedForRemove()
{
  //Az adott sor második cellája tartalmazza a csomagnevet
  QModelIndex temp = index.model()->index(index.row(), 1);

  Q_EMIT removeClicked(temp.model()->data(temp).toString());
}
