#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include <commandbar.h>
#include <QtWebKit>
#include <QtNetwork>
#include <QtGui>
#include <QAction>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(int argc,char** argv,QWidget *parent = 0);


protected slots:
    void changeLocation();
    void showLocation();
    void finishLoading(bool);
    void showProgress(int);
    void updateWindowTitle();
    void setWindowTitle(const QString &title);

private:
    int progress;
    CommandBar* command_bar;
    QWebView* view;
    QWidget* parent;

signals:
    
public slots:
    
};

#endif // BROWSER_H
