#include "commandbar.h"

CommandBar::CommandBar(QWidget *parent) :
    QLineEdit(parent)
{

}

void CommandBar::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace)
        if (text().length() == 0)
            setVisible(false);

    if (event->key() == Qt::Key_Escape)
        setVisible(false);

    //Skicka vidare eventet
    //emit keyPressed();
    QLineEdit::keyPressEvent(event);
}
