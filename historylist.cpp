#include "historylist.hpp"

HistoryList::HistoryList() :
  QStringList()
{

}

QString HistoryList::completion(QString str)
{
  //TODO: Kolla prestanda mot regexp filter()
  QStringList t;
  foreach(const QString &url, *this)
    if (url.startsWith(str, Qt::CaseInsensitive))
      t.push_back(url);

  t.sort();
  if (t.count() >= 1)
  {
    int len = qMin(t.first().length(), t.last().length());
    int shared = 0;
    for (; shared<len; ++shared)
      if (t.first().at(shared).toLower() != t.last().at(shared).toLower())
        break;
    return t.first().left(shared);
  }
  else
    return str;
}
