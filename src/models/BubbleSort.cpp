#include "BubbleSort.hpp"

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

BubbleSort::BubbleSort(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

BubbleSort::~BubbleSort()
{
    qDebug() << __FUNCTION__;
}

void BubbleSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void BubbleSort::run()
{
    qDebug() << "冒泡排序的线程的线程地址: " << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    int temp;
    for (int i = 0; i < m_list.size(); ++i) {
        for (int j = 0; j < m_list.size() - i - 1; ++j) {
            if (m_list[j] > m_list[j + 1]) {
                temp = m_list[j];
                m_list[j] = m_list[j + 1];
                m_list[j + 1] = temp;
            }
        }
    }
    int milsec = time.elapsed();
    qDebug() << "冒泡排序用时" << milsec << "毫秒";
    emit finish(m_list);
}
