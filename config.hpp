#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QMap>
#include <QVariant>
#include <QFile>
#include <QObject>
#include <QTextStream>
#include <QStringList>

bool canConvert(QVariant var, QVariant::Type type);

class Config : public QObject
{
    Q_OBJECT
  public:
    explicit Config(QObject *parent = NULL);
  private:
    QMap<QString, QVariant> settings_;
    QFile* configfile_;
    QTextStream config_;
};



#endif // CONFIG_HPP
