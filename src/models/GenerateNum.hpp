#pragma once

#include <QObject>
#include <QRunnable>

// 生成随机数
class GenerateNum
    : public QObject
    , public QRunnable
{
    Q_OBJECT

  public:
    explicit GenerateNum(QObject *parent = nullptr);
    ~GenerateNum() override;

    void recvNum(int num);

    void run() override;

  Q_SIGNALS:
    void sendArray(QVector<int> num);

  private:
    int m_num;
};