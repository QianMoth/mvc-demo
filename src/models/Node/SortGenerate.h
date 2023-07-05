#pragma once

#include <CGraph/CGraph>

#include "../Param/MyParam.h"

class SortGenerate : public CGraph::GNode
{
  public:
    CStatus init() override
    {
        CStatus status;
        status = CGRAPH_CREATE_GPARAM(MyParam, "param1");
        return status;
    }

    CStatus run() override
    {
        CGraph::CGRAPH_ECHO("[%s]", this->getName().c_str());

        auto *myParam = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, "param1");

        std::vector<int> _list;
        _list.reserve(20000);
        for (int i = 0; i < 20000; ++i) {
            _list.push_back(rand() % 100000);
        }

        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(myParam)
            myParam->list = _list;
        }

        return CStatus();
    }
};
