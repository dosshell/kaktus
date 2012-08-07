#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QNetworkCookieJar>
#include <QFile>
#include <QTextStream>

class CookieJar : public QNetworkCookieJar
{
    Q_OBJECT
  public:
    explicit CookieJar(QObject *parent = NULL);
    bool setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url);
    void setCookiesFromString(QString str);
  signals:
    void receivedCookie(const QList<QNetworkCookie> &cookieList, const QUrl &url);

  private:
    QFile* jarfile;
};

#endif // COOKIEJAR_H
