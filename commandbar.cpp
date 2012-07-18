#include "commandbar.h"

CommandBar::CommandBar(QWidget *parent) :
    QLineEdit(parent)
{

}

void CommandBar::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {

    case Qt::Key_Backspace:
        // Stäng commandbar om tom

        if (text().length() == 0)
            setVisible(false);
        break;

    case Qt::Key_Escape:
        // Avmarkera text
        // Stäng commandbar

        if (this->selectedText().length() == 0)
            setVisible(false);
        else
            this->setSelection(this->cursorPosition(), 0);
        break;
    default:
        break;
    }

    //Skicka vidare eventet
    //emit keyPressed();
    QLineEdit::keyPressEvent(event);
}
