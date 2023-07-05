#include "Controller.hpp"

#include <CGraph/CGraph>
#include <QDebug>

#include "models/Node/SortBubble.h"
#include "models/Node/SortGenerate.h"
#include "models/Node/SortQuick.h"
#include "models/Param/MyParam.h"

Controller *Controller::instance()
{
    static Controller controller;
    return &controller;
}

Controller::Controller() = default;

void Controller::start(int num)
{
    CGraph::GPipelinePtr pipeline = CGraph::GPipelineFactory::create();
    CStatus status;
    CGraph::GElementPtr gene = nullptr;
    CGraph::GElementPtr bubble = nullptr;
    CGraph::GElementPtr quick = nullptr;

    status += pipeline->registerGElement<SortGenerate>(&gene, {}, "Gene");
    status += pipeline->registerGElement<SortBubble>(&bubble, {gene}, "Bubble");
    status += pipeline->registerGElement<SortQuick>(&quick, {gene}, "Quick");
    if (!status.isOK()) {
        return;  // 使用时，请对所有CGraph接口的返回值做判定。本例子中省略
    }

    pipeline->init();

    pipeline->run();
    auto *randParam = pipeline->getGParam<MyParam>("param1");
    Q_EMIT sendRandResult(randParam->list);

    auto *bubbleResult = pipeline->getGParam<MyParam>("bubbleResult");
    Q_EMIT sendBubbleResult(bubbleResult->list);
    auto *quickResult = pipeline->getGParam<MyParam>("quickResult");
    Q_EMIT sendQuickResult(quickResult->list);

    pipeline->destroy();

    // status += pipeline->process();

    CGraph::GPipelineFactory::remove(pipeline);
}
