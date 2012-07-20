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
  {
    show();
    if (text().startsWith(":") || text().startsWith("#"))
    {
      //Visa nuvarande url och markera den
    }
  }
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


bool CommandBar::event(QEvent *e)
{
  if(e->type() == QEvent::KeyPress)
  {
    QKeyEvent *ke = static_cast<QKeyEvent *>(e);
    keyPressEvent(ke);
    return true;
  }
  else
    return QLineEdit::event(e);

}

void CommandBar::keyPressEvent(QKeyEvent *event)
{
  switch(event->key())
  {
    case Qt::Key_Tab:
      if (selectedText().length() > 0)
        setCursorPosition(selectionStart()+selectedText().length());
      break;

    case Qt::Key_Space:
      if (selectedText().length() > 0)
        setCursorPosition(selectionStart()+selectedText().length());
      QLineEdit::keyPressEvent(event);
      break;

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
  QString txt = text().trimmed();
  if (txt.length()>0)
  {
    QString cmd = txt;
    cmd.remove(0, 1);
    QProcess* procc;

    switch(text().at(0).toAscii())
    {
      case '#':
        procc = new QProcess(this);
        procc->start(cmd);
        break;

      case ':':
        setText(":Not valid yet :)");
        setSelection(1, 16);
        break;

      default:
        emit triggerUrl(QUrl(txt));
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
