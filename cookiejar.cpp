#include "cookiejar.hpp"

CookieJar::CookieJar(QObject *parent) :
  QNetworkCookieJar(parent)
{
  jarfile = new QFile("/tmp/kaktuskakor", this);
  if (jarfile->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    //Lägg till en massa cookies
    QTextStream jf(jarfile);
    setAllCookies(QNetworkCookie::parseCookies(jf.readAll().toAscii()));
  }
}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
  if (jarfile->isOpen())
  {
    QTextStream jf(jarfile);

    foreach(QNetworkCookie nc, cookieList)
      if (!nc.isSessionCookie())
        jf << nc.toRawForm() << endl;
  }

  return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}
