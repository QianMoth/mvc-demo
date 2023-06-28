#include "ListBox.hpp"

#include <QBoxLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QListWidget>
#include <QStandardItemModel>
#include <QTableView>

ListBox::ListBox(const QString &title, QWidget *parent, Qt::WindowFlags f) : QWidget(parent, f)
{
    setWindowTitle(title);
    setObjectName(title);
    setupUi();
}

void ListBox::setupUi()
{
    auto *layout = new QVBoxLayout(this);
    if (layout) {
        auto *groupBox = new QGroupBox(windowTitle(), this);
        if (groupBox) {
            layout->addWidget(groupBox);
            // groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
            auto *hLayout = new QHBoxLayout(groupBox);
            if (hLayout) {
                auto list = new QTableView(this);
                list->setSelectionBehavior(QAbstractItemView::SelectRows);
                list->setEditTriggers(QAbstractItemView::NoEditTriggers);
                list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                list->horizontalHeader()->setVisible(false);
                list->verticalHeader()->setVisible(false);
                if (list) {
                    hLayout->addWidget(list);
                    _model = new QStandardItemModel(list);
                    list->setModel(_model);
                }
                // list->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
            }
        }
    }
}

void ListBox::addItems(std::vector<int> list)
{
    _model->clear();
    for (auto num : list) {
        auto *item = new QStandardItem(QString::number(num));
        _model->appendRow(item);
    }
}