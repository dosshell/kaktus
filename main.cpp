#include <QApplication>
#include "mainwindow.hpp"

int main(int argc, char *argv[])
{


  QApplication q_application(argc, argv);
  QCoreApplication::setOrganizationName("kaktus");
  QCoreApplication::setApplicationName("kaktus");

  MainWindow *window = new MainWindow(argc, argv);
#if defined Q_OS_SYMBIAN || defined Q_WS_HILDON || defined Q_WS_MAEMO_5 || defined Q_WS_SIMULATOR
  window->showMaximized();
#else
  window->show();
#endif

  return q_application.exec();
}
