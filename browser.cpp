#include "browser.h"

Browser::Browser(QWidget *parent) :
    QWidget(parent)
{
    progress = 0;

    view = new QWebView(this);
    command_bar = new CommandBar(this);

    //Commandbar
    connect(command_bar, SIGNAL(returnPressed()), SLOT(changeLocation()));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));

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

//Kod ska flyttas till commandbar
void Browser::finishLoading(bool success)
{
    if (success == true)
    {

    }
    else
    {
        bool is_http = command_bar->text().startsWith("http:");
        bool is_https = command_bar->text().startsWith("https:");

        //If no http(s) try htpps
        if (!(is_http || is_https))
        {
            command_bar->setText(command_bar->text().prepend("https://"));
            changeLocation();
        }
        //Try http
        else if (is_https)
        {
            command_bar->setText(command_bar->text().remove(0, QString("https:").length()).prepend("http:"));
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
