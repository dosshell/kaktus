#ifndef HISTORYLIST_HPP
#define HISTORYLIST_HPP

#include <QStringList>

class HistoryList : public QStringList
{
  public:
    HistoryList();
    QString completion(QString str);

};

#endif // HISTORYLIST_HPP
