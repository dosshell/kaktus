#ifndef COMMANDBAR_H
#define COMMANDBAR_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QUrl>
#include <QString>
#include <QProcess>
#include "storagemanager.hpp"

class CommandBar : public QLineEdit
{
    Q_OBJECT
  public:
    explicit CommandBar(StorageManager* storemng, QWidget *parent = NULL);
    void hide();
    void show();

  public slots:
    void toggleInput();
    void reInput();
    void openExec();
    void openSetting();

  protected slots:
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *);
    bool event(QEvent *e);
  signals:
    void triggerUrl(QUrl url);
    void close();
    void open();

  private:
    void execute();
    StorageManager* storage;
};

#endif // COMMANDBAR_H
