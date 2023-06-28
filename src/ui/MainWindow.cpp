#include "MainWindow.hpp"

#include <QBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QString>

#include "components/ListBox.hpp"
#include "core/Controller.hpp"

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    setWindowTitle(tr("排序"));
    setupUi();

    connect(Controller::instance(), &Controller::sendRandResult, this, &MainWindow::showRand);
    connect(Controller::instance(), &Controller::sendBubbleResult, this, &MainWindow::showBubble);
    connect(Controller::instance(), &Controller::sendQuickResult, this, &MainWindow::showQuick);

    connect(this, &MainWindow::start, Controller::instance(), &Controller::start);
}

void MainWindow::setupUi()
{
    auto layout = new QVBoxLayout(this);
    if (layout) {
        layout->setSpacing(0);

        // 列表
        auto *hLayout = new QHBoxLayout();
        if (hLayout) {
            layout->addLayout(hLayout);

            randList = new ListBox(tr("随机数"), this);
            bubbleList = new ListBox(tr("冒泡排序"), this);
            quickList = new ListBox(tr("快速排序"), this);

            hLayout->addWidget(randList);
            hLayout->addWidget(bubbleList);
            hLayout->addWidget(quickList);
        }

        // 按钮
        auto *hLayout2 = new QHBoxLayout();
        if (hLayout2) {
            layout->addLayout(hLayout2);

            auto *startButton = new QPushButton(tr("开始"), this);
            hLayout2->addWidget(startButton);
            connect(startButton, SIGNAL(clicked(bool)), this, SLOT(startSort()));

            auto *stopButton = new QPushButton(tr("停止"), this);
            hLayout2->addWidget(stopButton);
        }
    }
}

void MainWindow::showRand(std::vector<int> list)
{
    randList->addItems(list);
}

void MainWindow::showBubble(std::vector<int> list)
{
    bubbleList->addItems(list);
}

void MainWindow::showQuick(std::vector<int> list)
{
    quickList->addItems(list);
}

void MainWindow::startSort()
{
    Q_EMIT start(20000);
}
