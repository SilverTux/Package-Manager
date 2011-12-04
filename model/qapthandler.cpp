#include "qapthandler.h"

QAptHandler::QAptHandler()
{
  m_backend = new QApt::Backend();
  m_backend->init();

  connect(m_backend, SIGNAL(packageChanged()), this, SIGNAL(updateStatusBar()));
  connect(m_backend, SIGNAL(workerEvent(QApt::WorkerEvent)), this, SIGNAL(workerEvent(QApt::WorkerEvent)));
  connect(m_backend, SIGNAL(downloadProgress(int, int, int)), 
          this, SIGNAL(downloadProgress(int, int, int)));
  connect(m_backend, SIGNAL(downloadMessage(int, const QString&)),
            this, SIGNAL(downloadMessage(int, const QString&)));
  connect(m_backend, SIGNAL(commitProgress(const QString&, int)),
            this, SIGNAL(commitProgress(const QString&, int)));
}

QAptHandler::~QAptHandler()
{
}

int QAptHandler::packageCount(QApt::Package::State state)
{
  return m_backend->packageCount(state);
}

int QAptHandler::packageCount()
{
  return m_backend->packageCount();
}

QApt::PackageList* QAptHandler::availablePackages() const
{
  QApt::PackageList *result = new QApt::PackageList();
  *result = m_backend->availablePackages();
  return result;
}

QApt::Package* QAptHandler::package(const QString &name) const
{
  return m_backend->package(name);
}

void QAptHandler::init()
{
  m_backend->init();
}

QApt::PackageList QAptHandler::markedPackages()
{
  return m_backend->markedPackages();
}

void QAptHandler::cancelDownload()
{
  m_backend->cancelDownload();
}

void QAptHandler::commitChanges()
{
  m_backend->commitChanges();
}
