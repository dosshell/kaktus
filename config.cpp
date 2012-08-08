#include "config.hpp"

//Todo: Snygga till detta... något arv eller något kul kanske :)
//Någon sorts bugg i qt4.3 med can Convert (ska fixas i qt5.0 så för göra så här
bool canConvert(QVariant var, QVariant::Type type)
{
  bool ok = false;
  switch (type)
  {
    case QVariant::Int:
      var.toInt(&ok);
      break;
    case QVariant::Double:
      var.toDouble(&ok);
      break;
    default:
      ok = false;
      break;
  }
  return ok;
}

Config::Config(QObject *parent) :
  QObject(parent), configfile_(NULL)
{
  //Fyll på med standardinställningar här
  settings_["text"] = "asd";
  settings_["int"] = 123;

  QString home = getenv("HOME");
  if (home.isEmpty())
    home = "~";
  configfile_ = new QFile(home + "/.kaktus/config", this);

  if (configfile_->open(QIODevice::ReadWrite | QIODevice::Text))
  {
    config_.setDevice(configfile_);
    while (!config_.atEnd())
    {
      QString line = config_.readLine();
      line.remove("#.*");
      QStringList keyvalued = line.split('=', QString::SkipEmptyParts);
      if (keyvalued.count() == 2)
      {
        QString key = keyvalued.first().trimmed();
        QVariant value = keyvalued.last().trimmed();

        if (canConvert(value, QVariant::Int))
          settings_.insert(key, value.toInt());
        else if (canConvert(value, QVariant::Double))
          settings_.insert(key, value.toDouble());
        else
          settings_.insert(key, value);
      }
    }
  }
}

