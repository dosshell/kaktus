#include "settings.hpp"

Settings::Settings(QObject *parent) :
  QSettings(parent)
{

}

QVariant Settings::valueAndUpdate(const QString &key, const QVariant &defaultValue)
{
  if (!contains(key))
    setValue(key, defaultValue);
  return value(key, defaultValue);
}
