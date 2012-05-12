#include <QApplication>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QMessageBox>

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

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
  init();
  setupUi();
  setupConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::init()
{
  m_pkgList = new PkgListWidget();
  m_pkgModel = new PkgListModel();
  m_cacheUpdateWidget = new CacheUpdateWidget();
  m_commitWidget = new CommitWidget();
  m_dependencyWidget = new DependencyWidget();
  m_packagePropertyWidget = new PkgPropertyWidget();
  m_helpWidget = new HelpWidget();
  m_aboutWidget = new AboutWidget();
  m_handler = QAptHandler::getInstance();
  m_idelegate = new InstalledDelegate();
  m_sectionList = new QListView();
  m_searchField = new QLineEdit();
  m_toolBar = new QToolBar();
  m_menuBar = new QMenuBar();
  m_applySearchButton = new QPushButton(trUtf8("Keresés"));
  m_applyButton = new QPushButton(trUtf8("Alkalmaz"));
  m_undoSelectionsButton = new QPushButton(trUtf8("Kijelölések megszüntetése"));
  m_propertyButton = new QPushButton(trUtf8("Tulajdonságok"));
  m_packageCountLabel = new QLabel(this);
  m_changedPackagesLabel = new QLabel(this);

  m_canExit = true;
  m_handler->init();
}

void MainWindow::setupUi()
{
  //Model and view setup
  m_pkgModel->setPkgList(m_handler->availablePackages());
  m_pkgList->setModel(m_pkgModel);
  m_pkgList->resizeColumnsToContents();
  m_pkgList->setItemDelegateForColumn(0,m_idelegate);
  m_pkgList->setSortingEnabled(true);

  QWidget *mainWidget = new QWidget();
  QHBoxLayout *mainLayout = new QHBoxLayout();
  QVBoxLayout *pkgLayout = new QVBoxLayout();
  QHBoxLayout *searchLayout = new QHBoxLayout();
  QLabel *searchLabel = new QLabel(trUtf8("Keresés csomagnév alapján:"));

  setDescriptions();
  setSectionList();

  m_applyButton->setEnabled(false);
  m_undoSelectionsButton->setEnabled(false);

  searchLayout->insertStretch(0,200);
  searchLayout->addWidget(searchLabel);
  searchLayout->addWidget(m_searchField);
  searchLayout->addWidget(m_applySearchButton);

  pkgLayout->addLayout(searchLayout);
  pkgLayout->addWidget(m_pkgList);
  pkgLayout->addWidget(m_packageLongDescriptionWidget);

  mainLayout->addWidget(m_sectionList);
  mainLayout->addLayout(pkgLayout);

  mainWidget->setLayout(mainLayout);
  setCentralWidget(mainWidget);

  //Setting up StatusBar
  statusBar()->addWidget(m_packageCountLabel);
  statusBar()->addWidget(m_changedPackagesLabel);
  statusBar()->show();

  updateStatusBar();

  //Setting up ToolBar
  QPixmap undop("images/undo.png");
  QPixmap applyp("images/apply.png");
  QPixmap propp("images/properties.png");
  QIcon undoIcon(undop);
  QIcon applyIcon(applyp);
  QIcon propIcon(propp);

  m_propertyButton->setEnabled(false);

  m_undoSelectionsButton->setIcon(undoIcon);
  m_applyButton->setIcon(applyIcon);
  m_propertyButton->setIcon(propIcon);
  m_toolBar->addWidget(m_undoSelectionsButton);
  m_toolBar->addWidget(m_applyButton);
  m_toolBar->addWidget(m_propertyButton);
  m_toolBar->setMovable(false);
  addToolBar(m_toolBar);

  //Setting up MenuBar
  m_file = m_menuBar->addMenu(trUtf8("&Fájl"));
  m_edit = m_menuBar->addMenu(trUtf8("Sz&erkesztés"));
  m_help = m_menuBar->addMenu(trUtf8("&Súgó"));
  m_helpAct = new QAction(trUtf8("Tartalom"), m_help);
  m_aboutAct = new QAction(trUtf8("Névjegy"), m_help);
  m_redoAct = new QAction(trUtf8("Újra"), m_edit);
  m_undoAct = new QAction(trUtf8("Visszavonás"), m_edit);
  m_saveAct = new QAction(trUtf8("Kijelölések mentése..."), m_file);
  m_loadAct = new QAction(trUtf8("Kijelölések betöltése..."), m_file);
  m_quitAct = new QAction(trUtf8("Kilépés"), m_file);

  m_file->addAction(m_saveAct);
  m_file->addAction(m_loadAct);
  m_file->addAction(m_quitAct);
  m_file->insertSeparator(m_quitAct);

  m_edit->addAction(m_undoAct);
  m_edit->addAction(m_redoAct);

  m_help->addAction(m_helpAct);
  m_help->addAction(m_aboutAct);

  //Setup the shortcuts
  m_undoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
  m_redoAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
  m_quitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
  m_saveAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
  m_loadAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));

  setEditActionsEnabled();

  setMenuBar(m_menuBar);

  connect(m_helpAct, SIGNAL(triggered()), m_helpWidget, SLOT(loadAndShow()));
  connect(m_aboutAct, SIGNAL(triggered()), m_aboutWidget, SLOT(show()));
  connect(m_redoAct, SIGNAL(triggered()), m_handler, SLOT(redo()));
  connect(m_undoAct, SIGNAL(triggered()), m_handler, SLOT(undo()));
  connect(m_saveAct, SIGNAL(triggered()), this, SLOT(saveToFile()));
  connect(m_loadAct, SIGNAL(triggered()), this, SLOT(loadFromFile()));
  connect(m_quitAct, SIGNAL(triggered()), this, SLOT(quitSlot()));

  setWindowTitle(trUtf8("Csomagkezelő"));
}

void MainWindow::setupConnections()
{
  connect(m_handler, SIGNAL(workerEvent(QApt::WorkerEvent)),
          this, SLOT(workerEvent(QApt::WorkerEvent)));
  connect(m_handler, SIGNAL(errorOccurred(QApt::ErrorCode, const QVariantMap&)),
          this, SLOT(errorOccurred(QApt::ErrorCode, const QVariantMap&)));
  connect(m_handler, SIGNAL(questionOccurred(QApt::WorkerQuestion, const QVariantMap&)),
          this, SLOT(questionOccurred(QApt::WorkerQuestion, const QVariantMap&)));
  connect(m_handler, SIGNAL(warningOccurred(QApt::WarningCode, const QVariantMap&)),
          this, SLOT(warningOccurred(QApt::WarningCode, const QVariantMap&)));
  connect(m_handler, SIGNAL(downloadProgress(int, int, int)),
          m_cacheUpdateWidget, SLOT(updateDownloadProgress(int, int, int)));
  connect(m_handler, SIGNAL(downloadMessage(int, const QString&)),
          m_cacheUpdateWidget, SLOT(updateDownloadMessage(int, const QString&)));
  connect(m_handler, SIGNAL(commitProgress(const QString&, int)),
          this, SLOT(updateCommitProgress(const QString&, int)));
  connect(m_handler, SIGNAL(packageChanged()), this, SLOT(packageChanged()));
  connect(m_pkgList, SIGNAL(clickedRow(QString)), this, SLOT(updateLabels(QString)));
  connect(m_pkgList, SIGNAL(doubleClickedRow(QString)), this, SLOT(addRemovePkg(QString)));
  connect(m_pkgList, SIGNAL(propertyClicked()), this, SLOT(showPropertyWidget()));
  connect(m_pkgList, SIGNAL(undoClicked(QString)), this, SLOT(removePkgFromSelected(QString)));
  connect(m_pkgList, SIGNAL(installClicked(QString)), this, SLOT(addRemovePkg(QString)));
  connect(m_pkgList, SIGNAL(removeClicked(QString)), this, SLOT(addRemovePkg(QString)));
  connect(m_pkgModel, SIGNAL(dataSorted()), m_pkgList, SLOT(reset()));
  connect(m_applySearchButton, SIGNAL(clicked()), this, SLOT(filterPkgListBySearch()));
  connect(m_searchField, SIGNAL(returnPressed()), this, SLOT(filterPkgListBySearch()));
  connect(m_applyButton, SIGNAL(clicked()), this, SLOT(commitAction()));
  connect(m_undoSelectionsButton, SIGNAL(clicked()), this, SLOT(undoSelections()));
  connect(m_propertyButton, SIGNAL(clicked()), this, SLOT(showPropertyWidget()));
}

//It sets the description widget
void MainWindow::setDescriptions()
{
  QVBoxLayout *dlayout = new QVBoxLayout();
  m_packageLongDescriptionWidget = new QWidget();
  m_longDescriptionBrowser = new QTextBrowser();

  dlayout->addWidget(m_longDescriptionBrowser);

  m_packageLongDescriptionWidget->setLayout(dlayout);
}

//It sets the sectionlist
void MainWindow::setSectionList()
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

void MainWindow::setUiEnabled(bool enabled)
{
    m_pkgList->setEnabled(enabled);
    m_sectionList->setEnabled(enabled);
    m_toolBar->setEnabled(enabled);
    m_longDescriptionBrowser->setEnabled(enabled);
    m_searchField->setEnabled(enabled);
    m_applySearchButton->setEnabled(enabled);
    m_menuBar->setEnabled(enabled);
    m_toolBar->setEnabled(enabled);
}

void MainWindow::setEditActionsEnabled()
{
    m_undoAct->setEnabled(!m_handler->isUndoStackEmpty());
    m_redoAct->setEnabled(!m_handler->isRedoStackEmpty());
}

void MainWindow::updateStatusBar()
{
    m_packageCountLabel->setText(QString(trUtf8("%1 Telepített, %2 Frissíthető, "
    "%3 Elérhető")).arg(m_handler->packageCount(QApt::Package::Installed)).arg(
            m_handler->packageCount(QApt::Package::Upgradeable)).arg(
                    m_handler->packageCount()));

    m_changedPackagesLabel->setText(QString(trUtf8("%1 Telepítésre kijelölt, "
    "%2 Frissítésre kijelölt, %3 Eltávolításra kijelölt")).arg(
            m_handler->packageCount(QApt::Package::ToInstall)).arg(
                    m_handler->packageCount(QApt::Package::ToUpgrade)).arg(
                            m_handler->packageCount(QApt::Package::ToRemove)));

}

void MainWindow::workerEvent(QApt::WorkerEvent event)
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
            m_canExit = false;
            m_commitWidget->clear();
            m_commitWidget->show();
            break;
        case QApt::CommitChangesFinished:
            m_canExit = true;
            m_commitWidget->close();
            m_handler->init();
            m_pkgModel->setPkgList(m_handler->availablePackages());
            m_pkgModel->clearSelected();
            m_pkgList->sortByColumn(1, Qt::DescendingOrder);
            m_handler->updateBeginCache();
            //We lock the ui in commitAction method
            setUiEnabled(true);
            setEditActionsEnabled();
            updateStatusBar();
            break;
        default:
            break;
    }
}

void MainWindow::errorOccurred(QApt::ErrorCode error, const QVariantMap &details)
{
    QString text;
    QString title;

    switch (error) {
        case QApt::AuthError:
            title = trUtf8("Hitelesítési hiba!");
            text = trUtf8("Ez a művelet nem folytatható megfelelő hitelesítés nélkül!");
            QMessageBox::critical(this, title, text);
            setUiEnabled(true);
            break;
        case QApt::CommitError:
            title = trUtf8("Hiba a módosítások alkalmazása közben!");
            text = trUtf8("A hiba oka: %1").arg(details["ErrorText"].toString());
            QMessageBox::critical(this, title, text);
            setUiEnabled(true);
            break;
        case QApt::InitError:
            title = trUtf8("Inicializálási hiba!");
            text = trUtf8("A csomagkezelő rendszert nem sikerült inicializálni! "
                          "Megsérülhetett a rendszere.");
            QMessageBox::critical(this, title, text);
            break;
        case QApt::LockError:
            title = trUtf8("Sikertelen zárolás!");
            text = trUtf8("Úgy látszik egy másik alkalmazás használja a csomagkezelő "
                          "rendszert. Zárjon be minden más csomagkezelőt mielőtt "
                          "módosításokat végez!");
            QMessageBox::critical(this, title, text);
            break;
        case QApt::DiskSpaceError:{
            QString drive = details["DirectoryString"].toString();
            title = trUtf8("Nincs elég szabad hely!");
            text = trUtf8("Nincs elég szabad hely a %1 meghajtón! "
                          "Szabadítson fel helyet a folytatáshoz.").arg(drive);
            QMessageBox::critical(this, title, text);
            break;
        }
        case QApt::FetchError:
            title = trUtf8("Letöltés meghiúsult!");
            text = trUtf8("Hiba lépett fel a letöltés közben!");
            QMessageBox::critical(this, title, text);
            break;
        case QApt::WorkerDisappeared:
            title = trUtf8("Váratlan hiba!");
            text = trUtf8("Úgy látszik hogy a qaptworker eltűnt vagy leállt! "
                          "Kérjük jelezze a hibát a Qapt karbantartóinak!");
            QMessageBox::critical(this, title, text);
            break;
        case QApt::UntrustedError:
            title = trUtf8("Nem megbízható csomagok!");
            text = trUtf8("A nem megbízható forrásból származó csomagok telepítése "
                          "le van tiltva a rendszerben!");
            QMessageBox::critical(this, title, text);
            break;
        default:
            setUiEnabled(true);
    }

    m_canExit = true;
    m_handler->init();
    if (m_commitWidget->isVisible())
        m_commitWidget->close();
    m_pkgModel->setPkgList(m_handler->availablePackages());
    m_pkgModel->clearSelected();
    m_pkgList->sortByColumn(1, Qt::DescendingOrder);
    m_handler->updateBeginCache();
    //We lock the ui in commitAction method
    setUiEnabled(true);
    setEditActionsEnabled();
    updateStatusBar();
}

void MainWindow::warningOccurred(QApt::WarningCode warning, const QVariantMap &details)
{
    switch (warning) {
        case QApt::FetchFailedWarning:{
          QString failedItem = details["FailedItem"].toString();
          QString warningText = details["WarningText"].toString();
          QString text = failedItem + warningText;
          QString title = trUtf8("Hiba történt letöltés közben!");
          QMessageBox::warning(this, title, text);
          break;
        }
        case QApt::UnknownWarning:
        default:
            QMessageBox::warning(this, trUtf8("Ismeretlen hiba!"),
                                 trUtf8("Ismeretlen hiba történt!"));
    }

    m_canExit = true;
    m_handler->init();
    if (m_commitWidget->isVisible())
        m_commitWidget->close();
    m_pkgModel->setPkgList(m_handler->availablePackages());
    m_pkgModel->clearSelected();
    m_pkgList->sortByColumn(1, Qt::DescendingOrder);
    m_handler->updateBeginCache();
    //We lock the ui in commitAction method
    setUiEnabled(true);
    setEditActionsEnabled();
    updateStatusBar();
}

void MainWindow::questionOccurred(QApt::WorkerQuestion question, const QVariantMap &details)
{
  QVariantMap response;
  QString title;
  QString text;

  switch (question) {
      case QApt::MediaChange: {
              QString media = details["Media"].toString();
              QString drive = details["Drive"].toString();

              title = trUtf8("A források megváltoztatása szükséges!");
              text = QString(trUtf8("Kérem töltse be a %1-t a %2-be")).arg(media).arg(drive);
              QMessageBox::information(this, title, text);

              response["MediaChanged"] = true;
              m_handler->answerWorkerQuestion(response);
      }
      case QApt::InstallUntrusted:{
              title = trUtf8("Nem hitelesített szoftver!");
              text = trUtf8("A telepítendő szoftver(ek) nem lettek hitelesítve."
                            "A nem hitelesített szoftverek biztonsági hibákat "
                            "tartalmazhatnak. Folytatja?");
              int result = QMessageBox::No;
              bool installUntrusted = false;

              result = QMessageBox::question(this,title,text,
                                                 QMessageBox::Yes|QMessageBox::No);
              switch (result) {
                  case QMessageBox::Yes:
                    installUntrusted = true;
                    break;
                  case QMessageBox::No:
                    installUntrusted = false;
                    break;
              }
              response["InstallUntrusted"] = installUntrusted;
              m_handler->answerWorkerQuestion(response);
      }
  }
}

void MainWindow::commitAction()
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
      m_handler->commitChanges();

      m_applyButton->setEnabled(false);
      m_undoSelectionsButton->setEnabled(false);
      m_propertyButton->setEnabled(false);
      setUiEnabled(false);
  }
}

void MainWindow::updateCommitProgress(const QString &message, int percentage)
{
    m_commitWidget->setLabelText(message);
    m_commitWidget->setProgress(percentage);
}

void MainWindow::updateLabels(QString name)
{
    QApt::Package *m_package = m_handler->package(name);

    // Gotta be careful when getting a package directly from the user's input. We can't currently
    // return empty Package containers when the package doesn't exist. And this is why most
    // package managers are MVC based. ;-)
    if (!(m_package == 0)) {
        QStringList *description = new QStringList;

        description->push_back(QString(trUtf8("<b>Csomag:</b> %1")).arg(m_package->name()));
        description->push_back(QString(trUtf8("<b>Csoport:</b> %1")).arg(m_package->section()));
        description->push_back(QString(trUtf8("<b>Származás:</b> %1")).arg(m_package->origin()));
        QString installedSize = QString::number(m_package->availableInstalledSize());
        description->push_back(QString(trUtf8("<b>Telepített méret:</b> %1 B")).arg(installedSize));
        description->push_back(QString(trUtf8("<b>Karbantartó:</b> %1")).arg(m_package->maintainer()));
        description->push_back(QString(trUtf8("<b>Forrás csomag:</b> %1")).arg(m_package->sourcePackage()));
        description->push_back(QString(trUtf8("<b>Verzió:</b> %1")).arg(m_package->version()));
        QString packageSize = QString::number(m_package->downloadSize());
        description->push_back(QString(trUtf8("<b>Letöltési méret:</b> %1 B")).arg(packageSize));
        description->push_back(QString(trUtf8("<b>Leírás:</b> %1")).arg(m_package->shortDescription()));
        description->push_back(QString(trUtf8("<b>Weboldal:</b> <a href=\"%1\">%2</a>")).arg(m_package->homepage()).arg(m_package->homepage()));

        m_packagePropertyWidget->setProperties(description);
        m_packagePropertyWidget->setDependencyList(m_package->dependencyList(false));

        m_longDescriptionBrowser->setText("<b>" + m_package->shortDescription() 
                                          + "</b> <br /><br />" + m_package->longDescription());
        m_propertyButton->setEnabled(true);

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

void MainWindow::showPropertyWidget()
{
  m_packagePropertyWidget->show();
}

//It filters by section
void MainWindow::filterPkgList(const QModelIndex &index)
{
  QString sectionStr = index.model()->data(index).toString();

  if (sectionStr != "Mind") {
      QApt::PackageList *result = new QApt::PackageList();
      QApt::PackageList *pkgL = m_handler->availablePackages();
  
      Q_FOREACH (QApt::Package *pkg, *pkgL) {
          if (sectionStr == pkg->section())
              result->push_back(pkg);
      }

      m_pkgModel->setPkgList(result);
  }
  else
    m_pkgModel->setPkgList(m_handler->availablePackages());

  m_pkgList->update();
}

void MainWindow::filterPkgListBySearch()
{
  QApt::PackageList *result = new QApt::PackageList();
  QApt::PackageList *pkgL = m_handler->availablePackages();
  
  Q_FOREACH (QApt::Package *pkg, *pkgL) {
    if (pkg->name().contains(m_searchField->text()))
        result->push_back(pkg);
  }

  m_pkgModel->setPkgList(result);
}

void MainWindow::saveToFile()
{
    QString caption = trUtf8("Fájl mentése");
    QString filter = trUtf8("Text files (*.txt)");
    QString path = QFileDialog::getSaveFileName(this, caption, "/home", filter);

    m_handler->saveSelections(path);
}

void MainWindow::loadFromFile()
{
    QString caption = trUtf8("Fájl megnyitása");
    QString filter = trUtf8("Text files (*.txt)");
    QString path = QFileDialog::getOpenFileName(this, caption, "/home", filter);

    m_handler->loadSelections(path);

    addPkgsToSelected();
}

void MainWindow::undoSelections()
{
  m_pkgModel->clearSelected();
  m_handler->restoreBeginCacheState();

  m_pkgList->reset();
  m_applyButton->setEnabled(false);
  m_undoSelectionsButton->setEnabled(false);
  m_propertyButton->setEnabled(false);

  m_undoAct->setEnabled(!m_handler->isUndoStackEmpty());
  m_redoAct->setEnabled(!m_handler->isRedoStackEmpty());
}

void MainWindow::addRemovePkg(QString name)
{
  //We push the current cache state to the undoStack
  m_handler->saveCacheState();

  QApt::Package *m_package = m_handler->package(name);
  QList<QString> selectInstall;
  QList<QString> selectRemove;
  QList<QString> selectUpgrade;

  if (!m_package->isInstalled()) {
      m_package->setInstall();
  } else {
      m_package->setRemove();
  }

  /*if (m_package->state() & QApt::Package::Upgradeable) {
      m_package->setInstall();
  }*/

  QApt::PackageList markedPkgs = m_handler->markedPackages();

  Q_FOREACH (QApt::Package *pkg, markedPkgs) {
      if (pkg->state() & QApt::Package::ToUpgrade)
          selectUpgrade.push_back(pkg->name());
      else if (pkg->state() & QApt::Package::ToInstall)
          selectInstall.push_back(pkg->name());
      else if (pkg->state() & QApt::Package::ToRemove)
          selectRemove.push_back(pkg->name());
  }

  m_pkgModel->addSelectedPkgs(selectInstall, selectRemove, selectUpgrade);

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

void MainWindow::addPkgsToSelected()
{
    QApt::PackageList markedPkgs = m_handler->markedPackages();
    QList<QString> selectInstall;
    QList<QString> selectRemove;
    QList<QString> selectUpgrade;

    Q_FOREACH (QApt::Package *pkg, markedPkgs) {
        if (pkg->state() & QApt::Package::ToUpgrade)
            selectUpgrade.push_back(pkg->name());
        else if (pkg->state() & QApt::Package::ToInstall)
            selectInstall.push_back(pkg->name());
        else if (pkg->state() & QApt::Package::ToRemove)
            selectRemove.push_back(pkg->name());
    }

    m_pkgModel->addSelectedPkgs(selectInstall, selectRemove, selectUpgrade);

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

void MainWindow::removePkgFromSelected(QString pkgName)
{
    QApt::Package *package = m_handler->package(pkgName);

    package->setKeep();

    m_pkgModel->removeSelectedPkg(pkgName);
}

void MainWindow::packageChanged()
{
  m_pkgModel->clearSelected();
  addPkgsToSelected();
  m_pkgList->reset();
  updateStatusBar();

  setEditActionsEnabled();
}

void MainWindow::quitSlot()
{
  //If we are committing we need to prevent to quit
  if (m_canExit)
      qApp->quit();
}

