#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    browser = new Browser(this);
    setCentralWidget(browser);
}


MainWindow::~MainWindow()
{

}
