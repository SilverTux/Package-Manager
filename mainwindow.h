#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QModelIndex>
#include <QTextBrowser>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QToolBar>
#include <QMenuBar>
#include <QProgressBar>

#include "view/pkglistwidget.h"
#include "view/cacheupdatewidget.h"
#include "view/commitwidget.h"
#include "view/dependencywidget.h"
#include "view/pkgpropertywidget.h"
#include "view/helpwidget.h"
#include "view/aboutwidget.h"
#include "model/pkglistmodel.h"
#include "model/qapthandler.h"
#include "model/installeddelegate.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

  protected Q_SLOTS:
    void updateStatusBar();
    void workerEvent(QApt::WorkerEvent event);
    void errorOccurred(QApt::ErrorCode error, const QVariantMap &details);
    void warningOccurred(QApt::WarningCode warning, const QVariantMap &details);
    void questionOccurred(QApt::WorkerQuestion question, const QVariantMap &details);
    void commitAction();
    void updateCommitProgress(const QString &message, int percentage);
    void updateLabels(QString name);
    void showPropertyWidget();
    void filterPkgList(const QModelIndex &index);
    void filterPkgListBySearch();
    void undoSelections();
    void addRemovePkg(QString name);
    void saveToFile();
    void loadFromFile();
    void addPkgsToSelected();
    void removePkgFromSelected(QString pkgName);
    void packageChanged();
    void quitSlot();

  private:
    void init();
    void setupUi();
    void setupConnections();
    void setDescriptions();
    void setSectionList();
    void setUiEnabled(bool enabled);
    void setEditActionsEnabled();

    PkgListWidget *m_pkgList;
    PkgListModel *m_pkgModel;
    CacheUpdateWidget *m_cacheUpdateWidget;
    CommitWidget *m_commitWidget;
    DependencyWidget *m_dependencyWidget;
    PkgPropertyWidget *m_packagePropertyWidget;
    HelpWidget *m_helpWidget;
    AboutWidget *m_aboutWidget;
    InstalledDelegate *m_idelegate;

    QStandardItemModel *m_sectionModel;

    QWidget *m_packageLongDescriptionWidget;
    QLabel *m_packageCountLabel;
    QLabel *m_changedPackagesLabel;
    QTextBrowser *m_longDescriptionBrowser;

    QListView *m_sectionList;
    QLineEdit *m_searchField;
    QPushButton *m_applySearchButton;
    QPushButton *m_applyButton;
    QPushButton *m_propertyButton;
    QPushButton *m_undoSelectionsButton;

    QToolBar *m_toolBar;
    QMenuBar *m_menuBar;

    QMenu *m_file;
    QMenu *m_edit;
    QMenu *m_help;
    QAction *m_helpAct;
    QAction *m_aboutAct;
    QAction *m_redoAct;
    QAction *m_undoAct;
    QAction *m_saveAct;
    QAction *m_loadAct;
    QAction *m_quitAct;

    bool m_canExit;
 
    QAptHandler *m_handler;
};

#endif //MAINWINDOW_H
