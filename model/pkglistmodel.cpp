#include "pkglistmodel.h"
#include <QDebug>

pkgListModel::pkgListModel(QAbstractTableModel *parent) : QAbstractTableModel(parent)
{
  m_data = new QList<QPair<bool, QList<QString> > >();
  m_selected = new QList<QString>();
  m_installed = new QList<QString>();
}

pkgListModel::~pkgListModel()
{
}

int pkgListModel::rowCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return m_data->size();
}

int pkgListModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);

  if (m_data->size() != 0)
      return m_data->at(0).second.size()+1;
  else
      return 4;
}

QVariant pkgListModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
      return QVariant();

  if (index.row() >= m_data->size() || index.row() < 0)
      return QVariant();

  if (role == Qt::BackgroundRole) {
      QModelIndex temp = index.model()->index(index.row(),1);

      //Ha kijelölünk egy csomagot és nincs telepítve akkor zölddel jelöljük a sort
      //ha telepítve van akkor pirossal, mert eltávolításra jelöltük ki
      if (m_selected->indexOf(temp.model()->data(temp).toString()) != -1 &&
          m_installed->indexOf(temp.model()->data(temp).toString()) == -1)
          return QVariant(QColor(Qt::green));
      else if (m_selected->indexOf(temp.model()->data(temp).toString()) != -1 &&
               m_installed->indexOf(temp.model()->data(temp).toString()) != -1)
          return QVariant(QColor(Qt::red));
      
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

bool pkgListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
/*  if (role == Qt::EditRole)
  {
    for (int col = 0; col < columnCount(index.parent()); ++col)
    {
      QModelIndex sibling = index.sibling(index.row(),col);
      setData(sibling, QColor(Qt::green), Qt::BackgroundColorRole);
    }
  }*/

  if (index.column() == 0) {
      int row = index.row();
      (*m_data)[row].first = value.toBool();
      return true;
  }
  else 
      return QAbstractTableModel::setData(index, value, role);
}

Qt::ItemFlags pkgListModel::flags(const QModelIndex &index) const
{
  Qt::ItemFlags flag = QAbstractTableModel::flags(index);
  if (index.column() == 0) {
      flag |= Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
  }

  return flag;
}

QVariant pkgListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole)
      return QVariant();

  if (orientation == Qt::Horizontal) {
      switch (section) {
         case 0:
             return trUtf8("Állapot");

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

void pkgListModel::setPkgList(QApt::PackageList* pkgList)
{
  reset();
  m_data->clear();
  m_installed->clear();

  //Üres csomaglistára nem csinálunk semmit
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

    /*for (int i = 0; i < m_data->size(); ++i)
    {
      if (m_data->size() != 0 && m_data->at(i).second.at(1) >= *pkg_name)
          m_data->insert(i,*temp);
    }

    if (m_data->size() == 0)*/
    m_data->push_back(*temp);


    if (pkg->isInstalled())
        m_installed->push_back(*pkg_name);
  }
}

QList<QString>& pkgListModel::selectedPkgs()
{
  QList<QString> *result = new QList<QString>();
  *result = *m_selected;

  return *result;
}

void pkgListModel::clearSelected()
{
  m_selected->clear();
  
  Q_EMIT selectedListCleared();
}

bool pkgListModel::isSelected(QString pkgName)
{
  if (m_selected->indexOf(pkgName) != -1)
      return true;
  else
      return false;
}

void pkgListModel::addRemoveSelectedPkgs(QList<QString> pkgL)
{
  qDebug() << "itt" << pkgL.size();

  Q_FOREACH (QString name, pkgL) {
    if (m_selected->indexOf(name) == -1)
        m_selected->push_back(name);
    else
        m_selected->removeAt(m_selected->indexOf(name));
  }

//  Q_EMIT selectedListChanged();
}
