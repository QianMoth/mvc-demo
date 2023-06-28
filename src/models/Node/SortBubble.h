#pragma once

#include "../Param/MyParam.h"
#include "CGraph.h"

class SortBubble : public CGraph::GNode
{
  public:
    CStatus init() override
    {
        CStatus status;
        status = CGRAPH_CREATE_GPARAM(MyParam, "bubbleResult");
        return status;
    }

    CStatus run() override
    {
        CGraph::CGRAPH_ECHO("[%s]", this->getName().c_str());

        auto myParam = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, "param1");

        std::vector<int> _list;
        {
            /* 对需要使用（读或写）参数的位置，加括号{}范围限定，以减少互斥等待时间 */
            CGRAPH_PARAM_READ_CODE_BLOCK(myParam)

            _list = myParam->list;
        }

        int temp;
        for (int i = 0; i < _list.size(); ++i) {
            for (int j = 0; j < _list.size() - i - 1; ++j) {
                if (_list[j] > _list[j + 1]) {
                    temp = _list[j];
                    _list[j] = _list[j + 1];
                    _list[j + 1] = temp;
                }
            }
        }

        auto *bubbleResult = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, "bubbleResult");
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(bubbleResult);
            bubbleResult->list = _list;
        }

        return CStatus();
    }
};
