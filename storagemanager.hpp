#ifndef STORAGEMANAGER_HPP
#define STORAGEMANAGER_HPP

#include <QObject>
#include "cookiejar.hpp"
#include "historylist.hpp"

class StorageManager : public QObject
{
    Q_OBJECT
  public:
    StorageManager(QObject *parent = NULL);
    CookieJar* cookieJar() {return cookiejar_;}
    HistoryList* history() {return &history_;}

  public slots:
    void storeCmd(QString cmd);

  protected slots:
    void storeCookie(const QList<QNetworkCookie> &cookieList, const QUrl &url);

  private:
    HistoryList history_;
    CookieJar* cookiejar_;

    QTextStream historyfile_;
    QTextStream jarfile_;
};

#endif // STORAGEMANAGER_HPP
