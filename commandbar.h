#ifndef COMMANDBAR_H
#define COMMANDBAR_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QUrl>
#include <QString>

class CommandBar : public QLineEdit
{
    Q_OBJECT
public:
    explicit CommandBar(QWidget *parent = 0);

public slots:
    void requestInput(QString prefix = "");
    void requestReInput();

protected slots:
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *);

signals:
    void triggerUrl(QUrl url);
    void abort();
    void open();

private:
    void hide();
    void show();
};

#endif // COMMANDBAR_H
