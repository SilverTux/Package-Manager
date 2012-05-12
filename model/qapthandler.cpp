#include "qapthandler.h"

QAptHandler *QAptHandler::instance=0;

QAptHandler::QAptHandler()
{
}

QAptHandler* QAptHandler::getInstance()
{
    //We shouldn't have more than one instance of this class because of apt Cache
    if (!instance)
        instance = new QAptHandler();

    return instance;
}

QAptHandler::~QAptHandler()
{
}

void QAptHandler::updateBeginCache()
{
    m_beginState = currentCacheState();
}

QApt::PackageList* QAptHandler::availablePackages()
{
    QApt::PackageList *result = new QApt::PackageList();
    *result = QApt::Backend::availablePackages();

    return result;
}

void QAptHandler::init()
{
    QApt::Backend::init();
    //We save the cache state after initialization
    m_beginState = currentCacheState();
}

void QAptHandler::commitChanges()
{
  m_debconfGui = new DebconfKde::DebconfGui("/tmp/qapt-sock");
  m_debconfGui->connect(m_debconfGui, SIGNAL(activated()), m_debconfGui, SLOT(show()));
  m_debconfGui->connect(m_debconfGui, SIGNAL(deactivated()), m_debconfGui, SLOT(hide()));

  QApt::Backend::commitChanges();
}

void QAptHandler::restoreBeginCacheState()
{
    restoreCacheState(m_beginState);
}

