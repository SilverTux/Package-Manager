#include <QApplication>
#include <iostream>

#include "mainwindow.h"

int main(int argc,char** argv)
{
  QApplication* qapp = new QApplication(argc,argv);
  MainWindow *mw = new MainWindow();

  mw->showMaximized();

  return qapp->exec();
}
