#ifndef STORAGEMANAGER_HPP
#define STORAGEMANAGER_HPP

class StorageManager : public QObject
{
    Q_OBJECT
  public:
    StorageManager(QWidget *parent = NULL);

  private:
    QStringList history;

    QFile* jarfile;
    QFile* history;
};

#endif // STORAGEMANAGER_HPP
