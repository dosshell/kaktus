#ifndef BROWSER_H
#define BROWSER_H

#include <QWidget>
#include <commandbar.hpp>
#include <QtWebKit>
#include <QtNetwork>
#include <QtGui>
#include <QAction>
#include <QShortcut>
#include <cookiejar.hpp>
#include "config.hpp"

class Browser : public QWidget
{
    Q_OBJECT
  public:
    explicit Browser(int argc,char** argv, QWidget *parent = NULL);

  protected slots:
    void setUrl(QUrl url);
    void finishLoading(bool);
    void updateWindowTitle(int progress=0);
    void setWindowTitle(const QString &title);

  private:
    CommandBar* command_bar;
    QWebView* view;
    QWidget* parent;
    QString last_requested_url;
  signals:
    
  public slots:
    
};

#endif // BROWSER_H
