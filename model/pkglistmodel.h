#ifndef PKGLISTMODEL_H
#define PKGLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QCheckBox>

#include <libqapt/package.h>

class pkgListModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    pkgListModel(QAbstractTableModel *parent = 0);
    ~pkgListModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setPkgList(QApt::PackageList *pkgList);
    QList<QString>& selectedPkgs();
    void clearSelected();
    bool isSelected(QString pkgName);

  public Q_SLOTS:
    void addRemoveSelectedPkgs(QList<QString> pkgL);

  Q_SIGNALS:
    void selectedListCleared();

  private:
    QList<QPair<bool, QList<QString> > > *m_data;
    QList<QString> *m_selected;
    QList<QString> *m_installed;
};

#endif //PKGLISTMODEL_H
