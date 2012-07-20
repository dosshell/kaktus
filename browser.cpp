#include "browser.h"


Browser::Browser(int argc,char** argv,QWidget *parent) :
  QWidget(parent)
{
  this->parent = parent;

  QNetworkProxyFactory::setUseSystemConfiguration(true);
  //QNetworkAccessManager::setCookieJar(new CookieJar(this));

  //View
  CookieJar* cj = new CookieJar(this);
  view = new QWebView(this);
  view->page()->networkAccessManager()->setCookieJar(cj);
  view->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
  view->settings()->setAttribute(QWebSettings::JavaEnabled, true);
  view->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
  view->settings()->setAttribute(QWebSettings::WebGLEnabled, true);
  view->settings()->setAttribute(QWebSettings::AutoLoadImages, true);

  //Commandbar
  command_bar = new CommandBar(this);
  connect(command_bar, SIGNAL(triggerUrl(QUrl)), SLOT(setUrl(QUrl)));

  //action and shortcuts for open commandbar
  //QAction *open_cb = new QAction(this);
  //QList<QKeySequence> ocb_l;
  //ocb_l << QKeySequence(Qt::CTRL + Qt::Key_L) << QKeySequence(Qt::SHIFT + Qt::Key_Period);
  //open_cb->setShortcuts(ocb_l);
  //addAction(open_cb);

  QShortcut* open_cb = new QShortcut(QKeySequence(Qt::Key_L + Qt::CTRL), this);
  QShortcut* exec_cb = new QShortcut(QKeySequence("#"), this);
  QShortcut* set_cb = new QShortcut(QKeySequence(":"), this);
  connect(open_cb, SIGNAL(activated()), command_bar, SLOT(toggleInput()));
  connect(exec_cb, SIGNAL(activated()), command_bar, SLOT(openExec()));
  connect(set_cb, SIGNAL(activated()), command_bar, SLOT(openSetting()));

  /* Show loading progress adn stuff */
  connect(view, SIGNAL(loadProgress(int)), this, SLOT(updateWindowTitle(int)));
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
  if(argc > 1)
    setUrl(QUrl(argv[1]));
  else
    setUrl(QUrl("https://www.google.com"));
}

void Browser::updateWindowTitle(int progress)
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

void Browser::setUrl(QUrl url)
{
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
      command_bar->reInput();
    }
  }
}
