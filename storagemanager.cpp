#include "storagemanager.hpp"

StorageManager::StorageManager(QObject *parent) :
  QObject(parent)
{
  cookiejar_ = new CookieJar(this);
  connect(cookiejar_, SIGNAL(receivedCookie(QList<QNetworkCookie>,QUrl)), this, SLOT(storeCookie(QList<QNetworkCookie>,QUrl)));

  //Load cookies
  QFile* jf = new QFile("/tmp/kaktuskakor", this);
  if (jf->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    //Lägg till en massa cookies
    jarfile_.setDevice(jf);
    cookiejar_->setCookiesFromString(jarfile_.readAll());
  }


  //Load history
  QFile* hf = new QFile("/tmp/historyfile", this);
  if (hf->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    historyfile_.setDevice(hf);
    history_.push_back("www.facebook.com");
    history_.push_back("www.google.com");
    history_.push_back("www.sweclockers.com");
    history_.push_back("www.swedroid.com");
    history_.push_back("www.svd.se");
    history_.push_back("www.dn.se");
  }
}

void StorageManager::storeCmd(QString cmd)
{
  history_.push_back(cmd);
  if (historyfile_.status() == QTextStream::Ok)
    historyfile_ << cmd << endl;
}

void StorageManager::storeCookie(const QList<QNetworkCookie> &cookieList, const QUrl &url)
{
  foreach(QNetworkCookie nc, cookieList)
    if (!nc.isSessionCookie() && jarfile_.status() == QTextStream::Ok)
      jarfile_ << nc.toRawForm() << endl;
}
