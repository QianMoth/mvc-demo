#pragma once

#include <QWidget>

class ListBox;

class MainWindow : public QWidget
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

  Q_SIGNALS:
    void start(int num);

  private:
    /// @brief ui界面
    void setupUi();

  private Q_SLOTS:
    void showRand(std::vector<int> list);
    void showBubble(std::vector<int> list);
    void showQuick(std::vector<int> list);

    /// @brief 开始生成随机数据并排序
    void startSort();

  private:
    ListBox *randList = nullptr;
    ListBox *bubbleList = nullptr;
    ListBox *quickList = nullptr;
};
