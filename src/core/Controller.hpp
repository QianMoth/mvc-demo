#pragma once

#include <QObject>

class BubbleSort;
class QuickSort;

class Controller : public QObject
{
    Q_OBJECT

  public:
    static Controller *instance();

  Q_SIGNALS:
    void sendRandResult(QVector<int> num);
    void sendBubbleResult(QVector<int> num);
    void sendQuickResult(QVector<int> num);

  public Q_SLOTS:
    void start(int num);
    void clear();

    void recvRand(QVector<int> num);

  private:
    Controller();

  private:
    BubbleSort *bubble = nullptr;
    QuickSort *quick = nullptr;

  private:
    Q_DISABLE_COPY(Controller);
};
