#include "Controller.hpp"

#include <QDebug>
#include <QThreadPool>

#include "models/BubbleSort.hpp"
#include "models/GenerateNum.hpp"
#include "models/QuickSort.hpp"

Controller *Controller::instance()
{
    static Controller controller;
    return &controller;
}

Controller::Controller()
{
    qDebug() << "maxThreadCount: " << QThreadPool::globalInstance()->maxThreadCount();
}

void Controller::start(int num)
{
    auto randNum = new GenerateNum();

    bubble = new BubbleSort;
    quick = new QuickSort;

    connect(randNum, &GenerateNum::sendArray, bubble, &BubbleSort::recvArray);
    connect(randNum, &GenerateNum::sendArray, quick, &QuickSort::recvArray);

    connect(randNum, &GenerateNum::sendArray, this, &Controller::recvRand);

    connect(bubble, &BubbleSort::finish, this,
            [=](QVector<int> num) { Q_EMIT sendBubbleResult(num); });

    connect(quick, &QuickSort::finish, this,
            [=](QVector<int> num) { Q_EMIT sendQuickResult(num); });

    randNum->recvNum(num);
    QThreadPool::globalInstance()->start(randNum);
}

void Controller::recvRand(QVector<int> num)
{
    QThreadPool::globalInstance()->start(bubble);
    QThreadPool::globalInstance()->start(quick);

    Q_EMIT sendRandResult(num);
}

void Controller::clear()
{
    qDebug() << __FUNCTION__;
    QThreadPool::globalInstance()->clear();
}