#pragma once

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

  public:
    static Controller *instance();

  Q_SIGNALS:
    void sendRandResult(std::vector<int> num);
    void sendBubbleResult(std::vector<int> num);
    void sendQuickResult(std::vector<int> num);

  public Q_SLOTS:
    void start(int num);

  private:
    Controller();

    Q_DISABLE_COPY(Controller);
};
