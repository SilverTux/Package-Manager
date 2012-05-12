#include <QDebug>

#include "pkglistmodel.h"

int PkgListModel::m_sortByColumn=0;

bool PkgListModel::pairLessThan(const QPair<bool, QList<QString> > &pair1,
                                const QPair<bool, QList<QString> > &pair2)
{
    switch (m_sortByColumn)
    {
    case 0:
        return pair1.first < pair2.first;
    case 1:
        return pair1.second.at(0) < pair2.second.at(0);
    case 2:
        return pair1.second.at(1) < pair2.second.at(1);
    case 3:
        return pair1.second.at(2) < pair2.second.at(2);
    }
}

bool PkgListModel::pairGreaterThan(const QPair<bool, QList<QString> > &pair1,
                                   const QPair<bool, QList<QString> > &pair2)
{
    switch (m_sortByColumn)
    {
    case 0:
        return pair1.first > pair2.first;
    case 1:
        return pair1.second.at(0) > pair2.second.at(0);
    case 2:
        return pair1.second.at(1) > pair2.second.at(1);
    case 3:
        return pair1.second.at(2) > pair2.second.at(2);
    }
}

PkgListModel::PkgListModel(QAbstractTableModel *parent) : QAbstractTableModel(parent)
{
  m_data = new QList<QPair<bool, QList<QString> > >();
  m_selectedInstall = new QList<QString>();
  m_selectedRemove = new QList<QString>();
  m_selectedUpgrade = new QList<QString>();
  m_installed = new QList<QString>();
}

PkgListModel::~PkgListModel()
{
}

int PkgListModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_data->size();
}

int PkgListModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);

  if (m_data->size() != 0)
      return m_data->at(0).second.size()+1;
  else
      return 4;
}

QVariant PkgListModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
      return QVariant();

  if (index.row() >= m_data->size() || index.row() < 0)
      return QVariant();

  if (role == Qt::BackgroundRole) {
      QModelIndex temp = index.model()->index(index.row(),1);

      //If we select a package and it isn't installed than we mark the row as green
      //If it installed we mark as red, because we select it to remove
      if (m_selectedInstall->indexOf(temp.model()->data(temp).toString()) != -1)
          return QVariant(QColor(Qt::green));
      else if (m_selectedRemove->indexOf(temp.model()->data(temp).toString()) != -1)
          return QVariant(QColor(Qt::red));
      else if (m_selectedUpgrade->indexOf(temp.model()->data(temp).toString()) != -1)
          return QVariant(QColor(Qt::yellow));
      
  }

  if (m_data->size() == 0)
      return QVariant();

  if (role == Qt::DisplayRole) {
      QPair<bool, QList<QString> > list = m_data->at(index.row());
      QString result;

      if (index.column() == 0 && (role == Qt::DisplayRole || role == Qt::EditRole))
      {
        return QVariant(list.first);
      }

      for (int i = 0; i < list.second.size(); ++i)
      {
        if (index.column() == i+1)
            result = list.second.at(i);
      }
     
      return result;
  }
  return QVariant();
}

bool PkgListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
      return QAbstractTableModel::setData(index, value, role);
}

QVariant PkgListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
      return QVariant();

  if (orientation == Qt::Horizontal) {
      switch (section) {
         case 0:
             return trUtf8("Á");

         case 1:
             return trUtf8("Név");

         case 2:
             return trUtf8("Verzió");

         case 3:
             return trUtf8("Leírás");

         default:
             return QVariant();
     }
  }
  return QVariant();
}

void PkgListModel::sort(int column, Qt::SortOrder order)
{
    m_sortByColumn = column;

    //If the arrow in the header is pointing up we get
    //Qt::DescendingOrder instead of Qt::Ascending order so
    //I swapped the two qSort-s
    switch(order)
    {
    case Qt::AscendingOrder:
        qSort(m_data->begin(),m_data->end(),pairGreaterThan);
        break;
    case Qt::DescendingOrder:
        qSort(m_data->begin(),m_data->end(),pairLessThan);
        break;
    }

    Q_EMIT dataSorted();
}

void PkgListModel::setPkgList(QApt::PackageList* pkgList)
{
  reset();
  m_data->clear();
  m_installed->clear();

  //If the package list is empty we do nothing
  if (pkgList->size() == 0)
      return;

  Q_FOREACH (QApt::Package *pkg, *pkgList) {
    QString *pkg_name = new QString(pkg->name());
    QString *pkg_version = new QString(pkg->version());
    QString *pkg_shortDescription = new QString(pkg->shortDescription());
    bool chk;

    QPair<bool, QList<QString> > *temp = new QPair<bool, QList<QString> >();
    
    pkg->isInstalled() ? chk=true : chk=false;
    temp->first = chk;
    temp->second.push_back(*pkg_name);
    temp->second.push_back(*pkg_version);
    temp->second.push_back(*pkg_shortDescription);

    m_data->push_back(*temp);


    if (pkg->isInstalled())
        m_installed->push_back(*pkg_name);
  }
}

QList<QString>& PkgListModel::selectedPkgs()
{
  QList<QString> *result = new QList<QString>();
  *result = *m_selectedInstall;

  return *result;
}

void PkgListModel::clearSelected()
{
  m_selectedInstall->clear();
  m_selectedRemove->clear();
  m_selectedUpgrade->clear();
  
  Q_EMIT selectedListCleared();
}

bool PkgListModel::isSelected(QString pkgName) const
{
  if (m_selectedInstall->indexOf(pkgName) != -1 ||
      m_selectedRemove->indexOf(pkgName) != -1 ||
      m_selectedUpgrade->indexOf(pkgName) != -1)
      return true;
  else
      return false;
}

void PkgListModel::addSelectedPkgs(QList<QString> sInstall,
                                   QList<QString> sRemove, QList<QString> sUpgrade)
{
  qDebug() << "itt" << sInstall.size();

  Q_FOREACH (QString name, sInstall) {
    if (m_selectedInstall->indexOf(name) == -1)
        m_selectedInstall->push_back(name);
  }

  Q_FOREACH (QString name, sRemove) {
    if (m_selectedRemove->indexOf(name) == -1)
        m_selectedRemove->push_back(name);
  }

  Q_FOREACH (QString name, sUpgrade) {
    if (m_selectedUpgrade->indexOf(name) == -1)
        m_selectedUpgrade->push_back(name);
  }
}

void PkgListModel::removeSelectedPkg(QString name)
{
    if (m_selectedInstall->indexOf(name) != -1)
        m_selectedInstall->removeAt(m_selectedInstall->indexOf(name));
    else if (m_selectedRemove->indexOf(name) != -1)
        m_selectedRemove->removeAt(m_selectedRemove->indexOf(name));
    else if (m_selectedUpgrade->indexOf(name) != -1)
        m_selectedUpgrade->removeAt(m_selectedUpgrade->indexOf(name));
}
