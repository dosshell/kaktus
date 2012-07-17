#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include <commandbar.h>
#include <QtWebKit>
#include <QtNetwork>
#include <QtGui>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);


protected slots:
    void changeLocation();
    void showLocation();
    void finishLoading(bool);

private:
    int progress;
    CommandBar* command_bar;
    QWebView* view;

signals:
    
public slots:
    
};

#endif // BROWSER_H
