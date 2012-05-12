#include "pkglistwidget.h"
#include "../model/pkglistmodel.h"

#include <QModelIndex>
#include <QMenu>
#include <QAction>

PkgListWidget::PkgListWidget(QWidget *parent) : QTableView(parent)
{
  setSelectionBehavior(QAbstractItemView::SelectRows);
  setContextMenuPolicy(Qt::CustomContextMenu);
  sortByColumn(1,Qt::DescendingOrder);
  connect(this, SIGNAL(clicked(const QModelIndex&)), this, SLOT(rowClicked(const QModelIndex&)));
  connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(rowDoubleClicked(const QModelIndex&)));
  connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(rightClickedCell(QPoint)));
}

PkgListWidget::~PkgListWidget()
{
}

void PkgListWidget::rowClicked(const QModelIndex &index)
{
  QModelIndex temp = index.model()->index(index.row(),1);

  Q_EMIT clickedRow(temp.model()->data(temp).toString());
}

void PkgListWidget::rowDoubleClicked(const QModelIndex &index)
{
  QModelIndex temp = index.model()->index(index.row(),1);

  Q_EMIT doubleClickedRow(temp.model()->data(temp).toString());
}

void PkgListWidget::rightClickedCell(QPoint point)
{
  m_index = indexAt(point);

  QPoint globalPos = mapToGlobal(point);
  QModelIndex temp = m_index.model()->index(m_index.row(), 0);
  const PkgListModel *itemp = dynamic_cast<const PkgListModel*>(temp.model());
  QString pkgName = m_index.model()->data(m_index.model()->index(m_index.row(), 1)).toString();

  QMenu myMenu;
  QAction *propertyAct = new QAction(trUtf8("Tulajdonságok"), this);
  QAction *undoSelection = new QAction(trUtf8("Kijelölés megszüntetése"), this);
  QAction *selectForInstall = new QAction(trUtf8("Kijelölés telepítésre"), this);
  QAction *selectForRemove = new QAction(trUtf8("Kijelölés eltávolításra"), this);

  if (itemp->isSelected(pkgName))
      undoSelection->setEnabled(true);
  else
      undoSelection->setEnabled(false);

  if (temp.model()->data(temp).toBool())
      selectForInstall->setEnabled(false);
  else
      selectForRemove->setEnabled(false);

  myMenu.addAction(undoSelection);
  myMenu.addAction(selectForInstall);
  myMenu.addAction(selectForRemove);
  myMenu.addSeparator();
  myMenu.addAction(propertyAct);

  connect(propertyAct, SIGNAL(triggered()), this, SIGNAL(propertyClicked()));
  connect(undoSelection, SIGNAL(triggered()), this, SLOT(undoSelection()));
  connect(selectForInstall, SIGNAL(triggered()), this, SLOT(selectedForInstall()));
  connect(selectForRemove, SIGNAL(triggered()), this, SLOT(selectedForRemove()));

  //Az adott sor második cellája tartalmazza a csomagnevet
  temp = m_index.model()->index(m_index.row(), 1);

  Q_EMIT clickedRow(temp.model()->data(temp).toString());

  myMenu.exec(globalPos);
}

void PkgListWidget::undoSelection()
{
    //Az adott sor második cellája tartalmazza a csomagnevet
    QModelIndex temp = m_index.model()->index(m_index.row(), 1);

    Q_EMIT undoClicked(temp.model()->data(temp).toString());
}

void PkgListWidget::selectedForInstall()
{
  //Az adott sor második cellája tartalmazza a csomagnevet
  QModelIndex temp = m_index.model()->index(m_index.row(), 1);

  Q_EMIT installClicked(temp.model()->data(temp).toString());
}

void PkgListWidget::selectedForRemove()
{
  //Az adott sor második cellája tartalmazza a csomagnevet
  QModelIndex temp = m_index.model()->index(m_index.row(), 1);

  Q_EMIT removeClicked(temp.model()->data(temp).toString());
}
