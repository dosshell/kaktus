#ifndef COMMANDBAR_H
#define COMMANDBAR_H

#include <QLineEdit>
#include <QKeyEvent>

class CommandBar : public QLineEdit
{
public:
    explicit CommandBar(QWidget *parent = 0);

protected slots:
    void keyPressEvent(QKeyEvent *event);
};

#endif // COMMANDBAR_H
