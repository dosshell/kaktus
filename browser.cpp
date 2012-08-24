#include "browser.hpp"


Browser::Browser(int argc,char** argv,QWidget *parent) :
  QWidget(parent)
{
  this->parent = parent;

  QNetworkProxyFactory::setUseSystemConfiguration(true);
  //QNetworkAccessManager::setCookieJar(new CookieJar(this));

  StorageManager* storage = new StorageManager(this);

  //View
  view = new QWebView(this);

  Settings q;

  view->page()->networkAccessManager()->setCookieJar(storage->cookieJar());

  view->settings()->setAttribute(QWebSettings::AutoLoadImages,                    q.valueAndUpdate("auto_load_images",                          true).toBool());
  view->settings()->setAttribute(QWebSettings::DnsPrefetchEnabled,                q.valueAndUpdate("dns_prefetch",                              false).toBool());
  view->settings()->setAttribute(QWebSettings::JavascriptEnabled,                 q.valueAndUpdate("javascript/enabled",                        false).toBool());
  view->settings()->setAttribute(QWebSettings::JavaEnabled,                       q.valueAndUpdate("java/enabled",                              false).toBool());
  view->settings()->setAttribute(QWebSettings::PluginsEnabled,                    q.valueAndUpdate("plugins/enabled",                           false).toBool());
  view->settings()->setAttribute(QWebSettings::PrivateBrowsingEnabled,            q.valueAndUpdate("private_browsing",                          false).toBool());
  view->settings()->setAttribute(QWebSettings::WebGLEnabled,                      q.valueAndUpdate("webgl/enabled",                             false).toBool());
  view->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows,          q.valueAndUpdate("javascript/can_open_windows",               false).toBool());
  view->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled,     q.valueAndUpdate("javascript/can_close_windows",              false).toBool());
  view->settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard,      q.valueAndUpdate("javascript/can_access_clipboard",           false).toBool());
  view->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled,            q.valueAndUpdate("dev_features",                              false).toBool());
  view->settings()->setAttribute(QWebSettings::SpatialNavigationEnabled,          q.valueAndUpdate("navigation/spatial_navigation",             false).toBool());
  view->settings()->setAttribute(QWebSettings::LinksIncludedInFocusChain,         q.valueAndUpdate("navigation/links_included_in_focus_chain",  false).toBool());
  view->settings()->setAttribute(QWebSettings::ZoomTextOnly,                      q.valueAndUpdate("navigation/zoom_text_only",                 false).toBool());
  view->settings()->setAttribute(QWebSettings::PrintElementBackgrounds,           q.valueAndUpdate("print_element_backgrounds",                 true).toBool());
  view->settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled,     q.valueAndUpdate("html5/offline_storage_database",            false).toBool());
  view->settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, q.valueAndUpdate("html5/offline_web_application_chache",      false).toBool());
  view->settings()->setAttribute(QWebSettings::LocalStorageEnabled,               q.valueAndUpdate("html5/locale_storage",                      false).toBool());
  view->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,   q.valueAndUpdate("local_content/can_access_remote_urls",      false).toBool());
  view->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,     q.valueAndUpdate("local_content/can_access_file_urls",        false).toBool());
  view->settings()->setAttribute(QWebSettings::XSSAuditingEnabled,                q.valueAndUpdate("xxs_auditing_enabled",                      false).toBool());
  view->settings()->setAttribute(QWebSettings::AcceleratedCompositingEnabled,     q.valueAndUpdate("rendering/use_cached_animation",            true).toBool());
  view->settings()->setAttribute(QWebSettings::TiledBackingStoreEnabled,          q.valueAndUpdate("rendering/accelerate_page_as_bitmap",       false).toBool());
  view->settings()->setAttribute(QWebSettings::FrameFlatteningEnabled,            q.valueAndUpdate("frame_flatting",                            false).toBool());
  view->settings()->setAttribute(QWebSettings::SiteSpecificQuirksEnabled,         q.valueAndUpdate("site_specific_quirks",                      false).toBool());
  q.sync();

  //Commandbar
  command_bar = new CommandBar(storage, this);
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
    setUrl(QUrl(q.value("homepage", "https://www.google.se").toString()));
}

void Browser::updateWindowTitle(int progress)
{
  if (progress <= 0

|| progress >= 100)
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
