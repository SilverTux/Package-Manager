#ifndef PKGLISTMODEL_H
#define PKGLISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QModelIndex>
#include <QCheckBox>

#include <libqapt/package.h>

class PkgListModel : public QAbstractTableModel
{
  Q_OBJECT

  public:
    PkgListModel(QAbstractTableModel *parent = 0);
    ~PkgListModel();

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);    
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void sort(int column, Qt::SortOrder order);
    void setPkgList(QApt::PackageList *pkgList);
    QList<QString>& selectedPkgs();
    void clearSelected();
    bool isSelected(QString pkgName) const;

  public Q_SLOTS:
    void addSelectedPkgs(QList<QString> sInstall,
                         QList<QString> sRemove, QList<QString> sUpgrade);
    void removeSelectedPkg(QString name);

  Q_SIGNALS:
    void selectedListCleared();
    void dataSorted();

  private:
    static bool pairLessThan(const QPair<bool, QList<QString> > &pair1,
                      const QPair<bool, QList<QString> > &pair2);
    static bool pairGreaterThan(const QPair<bool, QList<QString> > &pair1,
                         const QPair<bool, QList<QString> > &pair2);

    QList<QPair<bool, QList<QString> > > *m_data;
    QList<QString> *m_selectedInstall;
    QList<QString> *m_selectedRemove;
    QList<QString> *m_selectedUpgrade;
    QList<QString> *m_installed;

    static int m_sortByColumn;
};

#endif //PKGLISTMODEL_H
