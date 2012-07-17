#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include <commandbar.h>
#include <QtWebKit>

class Browser : public QWidget
{
    Q_OBJECT
public:
    explicit Browser(QWidget *parent = 0);

private:
    int progress;
    CommandBar* command_bar;
    QWebView* view;

signals:
    
public slots:
    
};

#endif // BROWSER_H
