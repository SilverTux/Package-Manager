#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QModelIndex>
#include <QTextBrowser>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>

#include "view/pkglistwidget.h"
#include "view/cacheupdatewidget.h"
#include "view/commitwidget.h"
#include "view/dependencywidget.h"
#include "model/pkglistmodel.h"
#include "model/qapthandler.h"
#include "model/installeddelegate.h"
#include "model/Debconf/DebconfGui.h"

/*#include <libqapt/globals.h>
#include <libqapt/backend.h>
#include <libqapt/package.h>*/

class mainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    mainWindow(QWidget *parent = 0);
    ~mainWindow();

    void setDescriptions();
    void setSectionList();

  public Q_SLOTS:
    void updateStatusBar();
    void workerEvent(QApt::WorkerEvent event);
    void commitAction();
    void updateDownloadProgress(int percentage, int speed, int ETA);
    void updateDownloadMessage(int flag, const QString &message);
    void updateCommitProgress(const QString &message, int percentage);
    void updateLabels(QString name);
    void showPropertyWidget();
    void filterPkgList(const QModelIndex &index);
    void filterPkgListBySearch();
    void markedPkgsClear();
    void undoSelections();
    void addRemovePkg(QString name);

  private:
    pkgListWidget *pkgList;
    pkgListModel *pkgModel;
    CacheUpdateWidget *m_cacheUpdateWidget;
    CommitWidget *m_commitWidget;
    DependencyWidget *m_dependencyWidget;
    InstalledDelegate *idelegate;

    QStandardItemModel *m_sectionModel;

    QWidget *m_packageDescriptionWidget;
    QWidget *m_packageLongDescriptionWidget;
    QLabel *m_packageCountLabel;
    QLabel *m_changedPackagesLabel;

    QLabel *m_nameLabel; 
    QLabel *m_sectionLabel;
    QLabel *m_originLabel;
    QLabel *m_installedSizeLabel;
    QLabel *m_maintainerLabel;
    QLabel *m_sourceLabel;
    QLabel *m_versionLabel;
    QLabel *m_packageSizeLabel;
    QLabel *m_shortDescriptionLabel;
    QLineEdit *m_longDescriptionLabel;
    QTextBrowser *m_longDescriptionBrowser;

    QListView *m_sectionList;
    QLineEdit *m_searchField;
    QPushButton *m_applySearchButton;
    QPushButton *m_applyButton;
    QPushButton *m_undoSelectionsButton;
 
    QAptHandler *m_handler;

    DebconfKde::DebconfGui *m_debconfGui;
};

#endif //MAINWINDOW_H
