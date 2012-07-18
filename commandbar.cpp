#include "commandbar.h"

CommandBar::CommandBar(QWidget *parent) :
    QLineEdit(parent)
{
    setVisible(false);
}

void CommandBar::requestInput(QString prefix)
{
    show();
}

void CommandBar::requestReInput()
{
    show();
    selectAll();
}

void CommandBar::focusOutEvent(QFocusEvent *event)
{
    hide();
    QLineEdit::focusOutEvent(event);
}

void CommandBar::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {

    case Qt::Key_Backspace:
        // Stäng commandbar om tom annars skicka vidare
        if (text().length() == 0)
            hide();
        else
            QLineEdit::keyPressEvent(event);
        break;

    case Qt::Key_Enter:
    case Qt::Key_Return:
        emit triggerUrl(QUrl(text()));
        setVisible(false);
        break;

    case Qt::Key_Escape:
        // Avmarkera text
        // Stäng commandbar
        if (this->selectedText().length() == 0)
            hide();
        else
            this->setSelection(this->cursorPosition(), 0);
        break;

    default:
        //skicka knappen vidare
        QLineEdit::keyPressEvent(event);
        break;
    }
}

void CommandBar::hide()
{
    setVisible(false);
    emit abort();
}

void CommandBar::show()
{
    setVisible(true);
    setFocus();
    emit open();
}
