#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <browser.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(int argc, char** argv,QWidget *parent = 0);
    ~MainWindow();

  private:
    Browser *browser;
};

#endif // MAINWINDOW_H
