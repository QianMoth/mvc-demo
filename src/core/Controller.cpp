#include "Controller.hpp"

#include <QDebug>

#include "CGraph.h"
#include "models/Node/SortBubble.h"
#include "models/Node/SortGenerate.h"
#include "models/Node/SortQuick.h"
#include "models/Param/MyParam.h"

using namespace CGraph;

Controller *Controller::instance()
{
    static Controller controller;
    return &controller;
}

Controller::Controller() {}

void Controller::start(int num)
{
    GPipelinePtr pipeline = GPipelineFactory::create();
    CStatus status;
    GElementPtr gene, bubble, quick = nullptr;

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

    GPipelineFactory::remove(pipeline);
}
