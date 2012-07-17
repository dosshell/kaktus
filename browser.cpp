#include "browser.h"

Browser::Browser(QWidget *parent) :
    QWidget(parent)
{
    progress = 0;

    view = new QWebView(this);
    command_bar = new CommandBar(this);

    //Commandbar
    connect(command_bar, SIGNAL(returnPressed()), SLOT(changeLocation()));
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(showLocation()));
    command_bar->setVisible(false);

    //Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(view);

    mainLayout->addWidget(command_bar);
    command_bar->setSizePolicy(QSizePolicy::Expanding, command_bar->sizePolicy().verticalPolicy());

    setLayout(mainLayout);

    //Startup
    view->load(QUrl("http://www.google.com"));

}


void Browser::showLocation()
{
    command_bar->setVisible(!command_bar->isVisible());
    command_bar->selectAll();
    command_bar->setFocus();
}

void Browser::changeLocation()
{
    QUrl url = QUrl(command_bar->text());
    command_bar->setVisible(false);
    view->setFocus();
    view->load(url);
}

void Browser::finishLoading(bool success)
{
    if (success == true)
    {

    }
    else
    {
        if (!command_bar->text().startsWith("http://") ||
                !command_bar->text().startsWith("https://"))
        {
            command_bar->setText(command_bar->text().prepend("http://"));
            changeLocation();
        }
        else
        {
            command_bar->setVisible(true);
            command_bar->setFocus();
            command_bar->selectAll();
        }
    }
}
