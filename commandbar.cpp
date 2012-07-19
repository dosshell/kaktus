#include "commandbar.h"

CommandBar::CommandBar(QWidget *parent) :
    QLineEdit(parent)
{
    setVisible(false);
}

void CommandBar::toggleInput()
{
    if (isVisible())
        hide();
    else
        show();
}

void CommandBar::reInput()
{
    show();
    selectAll();
}

void CommandBar::openExec()
{
    setVisible(true);
    setFocus();
    if (text().startsWith("#"))
        setSelection(1, text().length()-1);
    else
        setText("#");
}

void CommandBar::openSetting()
{
    setVisible(true);
    setFocus();
    if (text().startsWith(":"))
        setSelection(1, text().length()-1);
    else
        setText(":");
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

        // Execute, om det inte finns något så stäng
    case Qt::Key_Enter:
    case Qt::Key_Return:
        if (text().length() > 0)
            execute();
        else
            hide();
        break;

    case Qt::Key_Escape:
        // Avmarkera text
        // TODO: Ta fram riktiga urlen
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

void CommandBar::execute()
{
    if (text().length()>0)
    {
        QString cmd = text().remove(0, 1);
QProcess* procc = new QProcess(this);

        switch(text().at(0).toAscii())
        {
        case '#':

            procc->start(cmd);
            break;

        case ':':
            setText(":Not valid yet :)");
            setSelection(1, 16);
            break;

        default:
            emit triggerUrl(QUrl(text()));
            hide();
            break;
        }
    }
}

void CommandBar::hide()
{
    setVisible(false);
    emit close();
}

void CommandBar::show()
{
    setVisible(true);
    setFocus();
    emit open();
}
