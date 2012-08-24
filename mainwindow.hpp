#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <browser.hpp>

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(int argc, char** argv,QWidget *parent = NULL);
    ~MainWindow();

  private:
    void closeEvent(QCloseEvent *event);
    Browser *browser;
};

#endif // MAINWINDOW_H
