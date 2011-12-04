#include <QApplication>
#include <iostream>

#include "mainwindow.h"

/*!
	New A class!
*/
class A
{
  public:
	/*!
		\param x ezt használja fel számoláshoz!
	*/
	A(int x);
  private:
	int x;
};

int main(int argc,char** argv)
{
  QApplication* qapp = new QApplication(argc,argv);
  mainWindow *mw = new mainWindow();

  mw->showMaximized();

  return qapp->exec();
}
