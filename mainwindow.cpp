#include "mainwindow.h"

MainWindow::MainWindow(int argc,char** argv, QWidget *parent)
    : QMainWindow(parent)
{
    browser = new Browser(argc,argv,this);
    setCentralWidget(browser);
}


MainWindow::~MainWindow()
{

}
