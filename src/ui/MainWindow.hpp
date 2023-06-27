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
    void setupUi();

  private Q_SLOTS:
    void showRand(QVector<int> list);
    void showBubble(QVector<int> list);
    void showQuick(QVector<int> list);

    void startSort();

  private:
    ListBox *randList = nullptr;
    ListBox *bubbleList = nullptr;
    ListBox *quickList = nullptr;
};
