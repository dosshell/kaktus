#include "mainwindow.hpp"

MainWindow::MainWindow(int argc,char** argv, QWidget *parent) :
  QMainWindow(parent)
{
    browser = new Browser(argc,argv,this);
    setCentralWidget(browser);
}


MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
  QSettings q;
  q.sync();
  event->accept();
}
