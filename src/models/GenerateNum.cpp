#include "GenerateNum.hpp"

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

GenerateNum::GenerateNum(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

GenerateNum::~GenerateNum()
{
    qDebug() << __FUNCTION__;
}

void GenerateNum::recvNum(int num)
{
    m_num = num;
}

void GenerateNum::run()
{
    qDebug() << "生成随机数的线程的线程地址: " << QThread::currentThread();
    QVector<int> list;
    QElapsedTimer time;
    time.start();
    for (int i = 0; i < m_num; ++i) {
        list.push_back(rand() % 100000);
    }
    int milsec = time.elapsed();
    qDebug() << "生成" << m_num << "个随机数总共用时:" << milsec << "毫秒";
    Q_EMIT sendArray(list);
}