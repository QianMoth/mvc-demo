#include "QuickSort.hpp"

#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

QuickSort::QuickSort(QObject *parent) : QObject(parent), QRunnable()
{
    setAutoDelete(true);
}

void QuickSort::recvArray(QVector<int> list)
{
    m_list = list;
}

void QuickSort::run()
{
    qDebug() << "快速排序的线程的线程地址: " << QThread::currentThread();
    QElapsedTimer time;
    time.start();
    quickSort(m_list, 0, m_list.size() - 1);
    int milsec = time.elapsed();
    qDebug() << "快速排序用时" << milsec << "毫秒";
    emit finish(m_list);
}

void QuickSort::quickSort(QVector<int> &s, int l, int r)
{
    if (l < r) {
        int i = l, j = r;
        // 拿出第一个元素, 保存到x中,第一个位置成为一个坑
        int x = s[l];
        while (i < j) {
            // 从右向左找小于x的数
            while (i < j && s[j] >= x) {
                // 左移, 直到遇到小于等于x的数
                j--;
            }
            if (i < j) {
                // 将右侧找到的小于x的元素放入左侧坑中, 右侧出现一个坑
                // 左侧元素索引后移
                s[i++] = s[j];
            }

            // 从左向右找大于等于x的数
            while (i < j && s[i] < x) {
                // 右移, 直到遇到大于x的数
                i++;
            }
            if (i < j) {
                // 将左侧找到的元素放入右侧坑中, 左侧出现一个坑
                // 右侧元素索引向前移动
                s[j--] = s[i];
            }
        }
        // 此时 i=j,将保存在x中的数填入坑中
        s[i] = x;
        quickSort(s, l, i - 1);  // 递归调用
        quickSort(s, i + 1, r);
    }
}