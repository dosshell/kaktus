#include "cookiejar.h"

CookieJar::CookieJar(QObject *parent) :
    QNetworkCookieJar(parent)
{
    jarfile = new QFile("/tmp/test", this);
    if (jarfile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text))
    {
        //Lägg till en massa cookies
        //QNetworkCookie nc()
    }

}

bool CookieJar::setCookiesFromUrl(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
    if (jarfile->isOpen())
    {
        QTextStream jf(jarfile);

        jf << "----\n";
        foreach(QNetworkCookie nc, cookieList)
        {
            if (!nc.isSessionCookie())
            {
                //QString data(nc.toRawForm());
                //jf << data << "\n";
            }
        }
    }

    return QNetworkCookieJar::setCookiesFromUrl(cookieList, url);
}
