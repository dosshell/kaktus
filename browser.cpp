#include "browser.h"

Browser::Browser(QWidget *parent) :
    QWidget(parent)
{
    view = new QWebView(this);
    command_bar = new CommandBar(this);
    view->load(QUrl("http://www.google.com/ncr"));
}
