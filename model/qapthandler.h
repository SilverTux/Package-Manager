#ifndef QAPTHANDLER_H
#define QAPTHANDLER_H

#include <libqapt/backend.h>
#include <libqapt/package.h>
#include <libqapt/globals.h>
#include "Debconf/DebconfGui.h"

class QAptHandler : public QObject
{
  Q_OBJECT

  public:
    QAptHandler();
    ~QAptHandler();

    int packageCount(QApt::Package::State state);
    int packageCount();
    QApt::PackageList* availablePackages() const;
    QApt::Package* package(const QString &name) const;
    void init();
    QApt::PackageList markedPackages();

  public Q_SLOTS:
    void cancelDownload();
    void commitChanges();

  Q_SIGNALS:
    void updateStatusBar();
    void workerEvent(QApt::WorkerEvent event);
    void downloadProgress(int percentage, int speed, int ETA);
    void downloadMessage(int flag, const QString &message);
    void commitProgress(const QString &message, int percentage);

  private:
    QApt::Backend *m_backend;
    QApt::Package *m_package;
    QApt::Group *m_group;

    DebconfKde::DebconfGui *m_debconfGui;

};

#endif //QAPTHANDLER_H
