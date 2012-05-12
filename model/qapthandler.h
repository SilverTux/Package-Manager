#ifndef QAPTHANDLER_H
#define QAPTHANDLER_H

#include <libqapt/backend.h>
#include <libqapt/package.h>
#include <libqapt/globals.h>
#include "Debconf/DebconfGui.h"

class QAptHandler : public QApt::Backend
{
  Q_OBJECT

  public:
    static QAptHandler* getInstance();
    ~QAptHandler();

    void updateBeginCache();
    QApt::PackageList* availablePackages();
    void init();

  public Q_SLOTS:
    void commitChanges();
    void restoreBeginCacheState();

  private:
    QAptHandler();

    static QAptHandler *instance;

    QList<int> m_beginState;
    DebconfKde::DebconfGui *m_debconfGui;

};

#endif //QAPTHANDLER_H
