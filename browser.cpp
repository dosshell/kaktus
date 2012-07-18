#include "browser.h"


Browser::Browser(QWidget *parent) :
    QWidget(parent)
{
    progress = 0;
    this->parent = parent;

    //View
    view = new QWebView(this);
    view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    view->settings()->setAttribute(QWebSettings::JavaEnabled, true);
    view->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

    //Commandbar
    command_bar = new CommandBar(this);
    connect(command_bar, SIGNAL(triggerUrl(QUrl)), SLOT(setUrl(QUrl)));

    //action and shortcuts for open commandbar
    QAction *open_cb = new QAction(this);
    QList<QKeySequence> ocb_l;
    ocb_l << QKeySequence(Qt::CTRL + Qt::Key_L) << QKeySequence(Qt::SHIFT + Qt::Key_Period);
    open_cb->setShortcuts(ocb_l);
    addAction(open_cb);

    connect(open_cb, SIGNAL(triggered()), command_bar, SLOT(requestInput()));

    /* Show loading progress adn stuff */
    connect(view, SIGNAL(loadProgress(int)), this, SLOT(showProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(finishLoading(bool)));
    connect(view, SIGNAL(titleChanged(QString)), this, SLOT(updateWindowTitle()));

    //Layout
    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addWidget(view);

    mainLayout->addWidget(command_bar);
    command_bar->setSizePolicy(QSizePolicy::Expanding, command_bar->sizePolicy().verticalPolicy());

    setLayout(mainLayout);

    //Startup
    view->load(QUrl("https://www.google.com"));
    last_requested_url = "https://www.google.com";
}

void Browser::updateWindowTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void Browser::setWindowTitle(const QString &title)
{
    parent->setWindowTitle(QString("Kaktus - ") + title);
}

void Browser::showProgress(int p){
    progress = p;
    updateWindowTitle();
}

void Browser::setUrl(QUrl url)
{
    //view->stop(); //Behhövs den??
    last_requested_url = url.toString();
    view->load(url);
}

//Kod ska flyttas till commandbar
void Browser::finishLoading(bool success){
    if (success == true){
        updateWindowTitle();
    }
    else{
        bool is_http = last_requested_url.startsWith("http:");
        bool is_https = last_requested_url.startsWith("https:");

        //If no http(s) try http
        if (!(is_http || is_https))
        {
            setUrl(last_requested_url.prepend("http://"));
        }
        else
        {
            command_bar->requestReInput();
        }
    }
}
