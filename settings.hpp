#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>
#include <QVariant>

class Settings : public QSettings
{
    Q_OBJECT
  public:
    explicit Settings(QObject *parent = 0);
    QVariant valueAndUpdate(const QString &key, const QVariant &defaultValue);

  signals:
    
  public slots:
    
};

#endif // SETTINGS_HPP
