#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication q_application(argc, argv);

    MainWindow *window = new MainWindow(argc, argv);
    #if defined Q_OS_SYMBIAN || defined Q_WS_HILDON || defined Q_WS_MAEMO_5 || defined Q_WS_SIMULATOR
        window->showMaximized();
    #else
        window->show();
    #endif
    
    return q_application.exec();
}
