#ifndef COMMANDBAR_H
#define COMMANDBAR_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QUrl>
#include <QString>
#include <QProcess>

class CommandBar : public QLineEdit
{
    Q_OBJECT
  public:
    explicit CommandBar(QWidget *parent = 0);
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
    QStringList url_history;
    QStringList process_history;
    QStringList settings_history;
};

#endif // COMMANDBAR_H
