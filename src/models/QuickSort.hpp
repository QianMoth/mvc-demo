#pragma once

#include <QObject>
#include <QRunnable>

class QuickSort
    : public QObject
    , public QRunnable
{
    Q_OBJECT
  public:
    explicit QuickSort(QObject *parent = nullptr);

    void recvArray(QVector<int> list);

    void run() override;

  private:
    void quickSort(QVector<int> &list, int l, int r);

  signals:
    void finish(QVector<int> num);

  private:
    QVector<int> m_list;
};