#pragma once

#include <QWidget>

class QStandardItemModel;

class ListBox : public QWidget
{
    Q_OBJECT

  public:
    ListBox(const QString &title, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());

    void addItems(const std::vector<int> &list);

  private:
    void setupUi();

  private:
    QStandardItemModel *_model = nullptr;

  private:
    Q_DISABLE_COPY(ListBox);
};
