#include "mainwindow.h"

#include <QStandardItem>
#include <QList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QLineEdit>
#include <QSet>
#include <QModelIndex>
#include <QDebug>

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent)
{
  pkgList = new pkgListWidget();
  pkgModel = new pkgListModel();
  m_cacheUpdateWidget = new CacheUpdateWidget();
  m_commitWidget = new CommitWidget();
  m_dependencyWidget = new DependencyWidget();
  m_handler = new QAptHandler();
  idelegate = new InstalledDelegate();
  m_sectionList = new QListView();
  m_searchField = new QLineEdit();

  connect(m_handler, SIGNAL(updateStatusBar()), this, SLOT(updateStatusBar()));
  connect(m_handler, SIGNAL(workerEvent(QApt::WorkerEvent)), this, SLOT(workerEvent(QApt::WorkerEvent)));
  connect(m_handler, SIGNAL(downloadProgress(int, int, int)), 
          this, SLOT(updateDownloadProgress(int, int, int)));
  connect(m_handler, SIGNAL(downloadMessage(int, const QString&)), 
          this, SLOT(updateDownloadMessage(int, const QString&)));
  connect(m_handler, SIGNAL(commitProgress(const QString&, int)), 
          this, SLOT(updateCommitProgress(const QString&, int)));
  connect(pkgList, SIGNAL(clickedRow(QString)), this, SLOT(updateLabels(QString)));
  connect(pkgList, SIGNAL(doubleClickedRow(QString)), this, SLOT(addRemovePkg(QString)));
  connect(pkgList, SIGNAL(propertyClicked()), this, SLOT(showPropertyWidget()));
  connect(pkgList, SIGNAL(installClicked(QString)), this, SLOT(addRemovePkg(QString)));
  connect(pkgList, SIGNAL(removeClicked(QString)), this, SLOT(addRemovePkg(QString)));
  connect(pkgModel, SIGNAL(selectedListCleared()), this, SLOT(markedPkgsClear()));

  pkgModel->setPkgList(m_handler->availablePackages());
  pkgList->setModel(pkgModel);
  pkgList->resizeColumnsToContents();
  pkgList->setItemDelegateForColumn(0,idelegate);

  QWidget *mainWidget = new QWidget();
  QHBoxLayout *mainLayout = new QHBoxLayout();
  QVBoxLayout *pkgLayout = new QVBoxLayout();
  QHBoxLayout *searchLayout = new QHBoxLayout();
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  QLabel *searchLabel = new QLabel(trUtf8("Keresés csomagnév alapján:"));
  setDescriptions();
  setSectionList();

  m_applySearchButton = new QPushButton(trUtf8("Keresés"));
  connect(m_applySearchButton, SIGNAL(clicked()), this, SLOT(filterPkgListBySearch()));
  connect(m_searchField, SIGNAL(returnPressed()), this, SLOT(filterPkgListBySearch()));

  m_applyButton = new QPushButton(trUtf8("Alkalmaz"));
  m_applyButton->setEnabled(false);
  connect(m_applyButton, SIGNAL(clicked()), this, SLOT(commitAction()));

  m_undoSelectionsButton = new QPushButton(trUtf8("Kijelölések megszüntetése"));
  m_undoSelectionsButton->setEnabled(false);
  connect(m_undoSelectionsButton, SIGNAL(clicked()), this, SLOT(undoSelections()));

  searchLayout->insertStretch(0,200);
  searchLayout->addWidget(searchLabel);
  searchLayout->addWidget(m_searchField);
  searchLayout->addWidget(m_applySearchButton);

  buttonLayout->addWidget(m_undoSelectionsButton);
  buttonLayout->addWidget(m_applyButton);

  pkgLayout->addLayout(searchLayout);
  pkgLayout->addWidget(pkgList);
  pkgLayout->addWidget(m_packageLongDescriptionWidget);
  pkgLayout->addLayout(buttonLayout);

  mainLayout->addWidget(m_sectionList);
  mainLayout->addLayout(pkgLayout);

  mainWidget->setLayout(mainLayout);
  setCentralWidget(mainWidget);

  m_packageCountLabel = new QLabel(this);
  m_changedPackagesLabel = new QLabel(this);
  statusBar()->addWidget(m_packageCountLabel);
  statusBar()->addWidget(m_changedPackagesLabel);
  statusBar()->show();

  updateStatusBar();
}

mainWindow::~mainWindow()
{
}

void mainWindow::setDescriptions()
{
  m_packageDescriptionWidget = new QWidget();
  m_packageLongDescriptionWidget = new QWidget();

  QVBoxLayout *layout = new QVBoxLayout();
  QVBoxLayout *dlayout = new QVBoxLayout();

  m_nameLabel = new QLabel();
  m_sectionLabel = new QLabel();
  m_originLabel = new QLabel();
  m_installedSizeLabel = new QLabel();
  m_maintainerLabel = new QLabel();
  m_sourceLabel = new QLabel();
  m_versionLabel = new QLabel();
  m_packageSizeLabel = new QLabel();
  m_shortDescriptionLabel = new QLabel();
  m_longDescriptionLabel = new QLineEdit();
  m_longDescriptionBrowser = new QTextBrowser();

  layout->addWidget(m_nameLabel);
  layout->addWidget(m_sectionLabel);
  layout->addWidget(m_originLabel);
  layout->addWidget(m_installedSizeLabel);
  layout->addWidget(m_maintainerLabel);
  layout->addWidget(m_sourceLabel);
  layout->addWidget(m_versionLabel);
  layout->addWidget(m_packageSizeLabel);
  layout->addWidget(m_shortDescriptionLabel);
  layout->addWidget(m_longDescriptionLabel);
  dlayout->addWidget(m_longDescriptionBrowser);

  m_packageDescriptionWidget->setLayout(layout);
  m_packageLongDescriptionWidget->setLayout(dlayout);
}

void mainWindow::setSectionList()
{
  QApt::PackageList *pkgL = m_handler->availablePackages();
  QSet<QString> set;
  m_sectionModel = new QStandardItemModel();

  Q_FOREACH (QApt::Package *pkg, *pkgL)
    set.insert(pkg->section());
    

  QSet<QString>::const_iterator i = set.constBegin();
  QStandardItem *item; 
  
  while (i != set.constEnd()) {
    item = new QStandardItem(QString(*i));
    m_sectionModel->appendRow(item);
    ++i;
  }

  m_sectionModel->sort(0,Qt::AscendingOrder);

  item = new QStandardItem(QString("Mind"));
  m_sectionModel->insertRow(0,item);
  

  m_sectionList->setModel(m_sectionModel);
  m_sectionList->setMaximumWidth(150);
  m_sectionList->setEditTriggers(QAbstractItemView::NoEditTriggers);

  connect(m_sectionList, SIGNAL(clicked(const QModelIndex&)), 
          this, SLOT(filterPkgList(const QModelIndex&)));
}

void mainWindow::updateStatusBar()
{
    m_packageCountLabel->setText(QString(trUtf8("%1 Telepített, %2 Frissíthető, %3 Elérhető")).arg(m_handler->packageCount(QApt::Package::Installed)).arg(m_handler->packageCount(QApt::Package::Upgradeable)).arg(m_handler->packageCount()));

    m_changedPackagesLabel->setText(QString(trUtf8("%1 Telepítésre kijelölt, %2 Frissítésre kijelölt, %3 Eltávolításra kijelölt")).arg(m_handler->packageCount(QApt::Package::ToInstall)).arg(m_handler->packageCount(QApt::Package::ToUpgrade)).arg(m_handler->packageCount(QApt::Package::ToRemove)));

}

void mainWindow::workerEvent(QApt::WorkerEvent event)
{
    switch (event) {
        case QApt::CacheUpdateStarted:
            m_cacheUpdateWidget->clear();
            m_cacheUpdateWidget->setHeaderText("<b>Szoftver források frissítése</b>");
            m_cacheUpdateWidget->show();
            connect(m_cacheUpdateWidget, SIGNAL(cancelCacheUpdate()), m_handler, SLOT(cancelDownload()));
            break;
        case QApt::CacheUpdateFinished:
            updateStatusBar();
            m_cacheUpdateWidget->close();
            break;
        case QApt::PackageDownloadStarted:
            m_cacheUpdateWidget->clear();
            m_cacheUpdateWidget->setHeaderText("<b>Csomagok letöltése</b>");
            m_cacheUpdateWidget->show();
            connect(m_cacheUpdateWidget, SIGNAL(cancelCacheUpdate()), m_handler, SLOT(cancelDownload()));
            break;
        case QApt::PackageDownloadFinished:
            updateStatusBar();
            m_cacheUpdateWidget->close();
            break;
        case QApt::CommitChangesStarted:
            m_commitWidget->clear();
            m_commitWidget->show();
            break;
        case QApt::CommitChangesFinished:
            updateStatusBar();
            m_commitWidget->close();
            m_handler->init();
            pkgModel->setPkgList(m_handler->availablePackages());
	    pkgModel->clearSelected(); 
            break;
        default:
            break;
    }
}

void mainWindow::commitAction()
{
  QApt::PackageList pkgL = m_handler->markedPackages();
  QList<QString> *resultInstall = new QList<QString>();
  QList<QString> *resultRemove = new QList<QString>();
  
  //Szétválogatjuk a módosítandó csomagokat telepítendő és eltávolítandó csoportokba
  //ToInstall = 1 << 1; ToRemove = 1 << 6
  //Egyszerre több állípota is lehet a csomagnak, pl.: NewInstall, NotInstalled és ToInstall
  //ezért logikai és-t használunk
  Q_FOREACH (QApt::Package *pkg, pkgL) {
    if ((pkg->state() & QApt::Package::ToInstall) == QApt::Package::ToInstall)
      resultInstall->push_back(pkg->name());
    else if ((pkg->state() & QApt::Package::ToRemove) == QApt::Package::ToRemove)
      resultRemove->push_back(pkg->name());
  }

  m_dependencyWidget->clear();
  m_dependencyWidget->setPkgs(resultInstall, resultRemove);

  if (m_dependencyWidget->exec()) {
      m_debconfGui = new DebconfKde::DebconfGui("/tmp/qapt-sock",this);
      m_debconfGui->connect(m_debconfGui, SIGNAL(activated()), m_debconfGui, SLOT(show()));
      m_debconfGui->connect(m_debconfGui, SIGNAL(deactivated()), m_debconfGui, SLOT(hide()));

      m_handler->commitChanges();

      m_applyButton->setEnabled(false);
  }
}

void mainWindow::updateDownloadProgress(int percentage, int speed, int ETA)
{
  m_cacheUpdateWidget->setTotalProgress(percentage, speed, ETA);
}

void mainWindow::updateDownloadMessage(int flag, const QString &message)
{
    QString fullMessage;

    switch (flag) {
      case QApt::DownloadFetch:
          fullMessage = "Letöltés: %1";
          break;
      case QApt::HitFetch:
          fullMessage = "Ellenőrzés: %1";
          break;
      case QApt::IgnoredFetch:
          fullMessage = "Elvet: %1";
          break;
      default:
          fullMessage = message;
    }
    m_cacheUpdateWidget->addItem(fullMessage);

}

void mainWindow::updateCommitProgress(const QString &message, int percentage)
{
    m_commitWidget->setLabelText(message);
    m_commitWidget->setProgress(percentage);
}

void mainWindow::updateLabels(QString name)
{
    QApt::Package *m_package = m_handler->package(name);

    // Gotta be careful when getting a package directly from the user's input. We can't currently
    // return empty Package containers when the package doesn't exist. And this is why most
    // package managers are MVC based. ;-)
    if (!(m_package == 0)) {
        m_nameLabel->setText(QString(trUtf8("<b>Csomag:</b> %1")).arg(m_package->name()));
        m_sectionLabel->setText(QString(trUtf8("<b>Csoport:</b> %1")).arg(m_package->section()));
        m_originLabel->setText(QString(trUtf8("<b>Származás:</b> %1")).arg(m_package->origin()));
        QString installedSize = QString::number(m_package->availableInstalledSize());
        m_installedSizeLabel->setText(QString(trUtf8("<b>Telepített méret:</b> %1 B")).arg(installedSize));
        m_maintainerLabel->setText(QString(trUtf8("<b>Karbantartó:</b> %1")).arg(m_package->maintainer()));
        m_sourceLabel->setText(QString(trUtf8("<b>Forrás csomag:</b> %1")).arg(m_package->sourcePackage()));
        m_versionLabel->setText(QString(trUtf8("<b>Verzió:</b> %1")).arg(m_package->version()));
        QString packageSize = QString::number(m_package->downloadSize());
        m_packageSizeLabel->setText(QString(trUtf8("<b>Letöltési méret:</b> %1 B")).arg(packageSize));
        m_shortDescriptionLabel->setText(QString(trUtf8("<b>Leírás:</b> %1")).arg(m_package->shortDescription()));
        m_longDescriptionLabel->setText(m_package->longDescription());
        m_longDescriptionBrowser->setText("<b>" + m_package->shortDescription() 
                                          + "</b> <br /><br />" + m_package->longDescription());

    }

    // Uncomment these to see the results in Konsole; I was too lazy to make a GUI for them

    // kDebug() << "============= New package Listing =============";
    // QStringList requiredByList(m_package->requiredByList());
    // Q_FOREACH (const QString &name, requiredByList) {
        // kDebug() << "reverse dependency: " << name;
    // }

    // A convenient way to check the install status of a package
    // if (m_package->isInstalled()) {
        // kDebug() << "Package is installed!!!";
    // }

}

void mainWindow::showPropertyWidget()
{
  m_packageDescriptionWidget->show();
}

void mainWindow::filterPkgList(const QModelIndex &index)
{
  QString sectionStr = index.model()->data(index).toString();

  if (sectionStr != "Mind") {
      QApt::PackageList *result = new QApt::PackageList();
      QApt::PackageList *pkgL = m_handler->availablePackages();
  
      Q_FOREACH (QApt::Package *pkg, *pkgL) {
          if (sectionStr == pkg->section())
              result->push_back(pkg);
      }

      pkgModel->setPkgList(result);
  }
  else
    pkgModel->setPkgList(m_handler->availablePackages());

  pkgList->update();
}

void mainWindow::filterPkgListBySearch()
{
  QApt::PackageList *result = new QApt::PackageList();
  QApt::PackageList *pkgL = m_handler->availablePackages();
  
  Q_FOREACH (QApt::Package *pkg, *pkgL) {
    if (pkg->name().contains(m_searchField->text()))
        result->push_back(pkg);
  }

  pkgModel->setPkgList(result); 
}

void mainWindow::markedPkgsClear()
{
  QApt::PackageList keepPkgL = m_handler->markedPackages();

  Q_FOREACH (QApt::Package *pkg, keepPkgL) {
    pkg->setKeep();
    qDebug() << pkg->name() << " jelolese Keep-re";
  }

  m_applyButton->setEnabled(false);
  m_undoSelectionsButton->setEnabled(false);


  updateStatusBar();
}

void mainWindow::undoSelections()
{
  pkgModel->clearSelected();
}

void mainWindow::addRemovePkg(QString name)
{
/*  QList<QString> depPkgs = m_handler->package(name)->dependencyList(false);
  QList<QString> result;

  result.push_back(name);

  qDebug() << name << "---";
  qDebug() << m_handler->package(name)->suggestsList();

  //A kijelölt csomag függőségeinek megjelölése a pkgmodellben
  Q_FOREACH(QString pkg, depPkgs)
  {
    QString pkgName = pkg.split("</b> ").at(1).split(" ").at(0);
    QApt::Package *tPkg = m_handler->package(pkgName);

    if ( !(tPkg->isInstalled()) )
    {
//        result.push_back(pkg.split("> ").at(1).split(" ").at(0));
        addRemovePkg(pkgName);
    }
    qDebug() << pkgName << "->" << name ;
  }

  pkgModel->addRemoveSelectedPkgs(result);*/

  QApt::Package *m_package = m_handler->package(name);
  QList<QString> result;

  if (!m_package->isInstalled()) {
      m_package->setInstall();
  } else {
      m_package->setRemove();
  }

  if (m_package->state() & QApt::Package::Upgradeable) {
      m_package->setInstall();
  }

  QApt::PackageList markedPkgs = m_handler->markedPackages();

  Q_FOREACH (QApt::Package *pkg, markedPkgs) {
    result.push_back(pkg->name());
  }

  pkgModel->addRemoveSelectedPkgs(result);

  if (m_handler->markedPackages().size() > 0) {
      m_applyButton->setEnabled(true);
      m_undoSelectionsButton->setEnabled(true);
  }
  else {
      m_applyButton->setEnabled(false);
      m_undoSelectionsButton->setEnabled(false);
  }
  
  updateStatusBar();
}
