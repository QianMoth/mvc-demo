#pragma once

#include <QObject>
#include <QRunnable>

class BubbleSort
    : public QObject
    , public QRunnable
{
    Q_OBJECT
  public:
    explicit BubbleSort(QObject *parent = nullptr);
    ~BubbleSort();

    void recvArray(QVector<int> list);

    void run() override;

  signals:
    void finish(QVector<int> num);

  private:
    QVector<int> m_list;
};
