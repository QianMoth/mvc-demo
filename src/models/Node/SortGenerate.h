#pragma once

#include "../Param/MyParam.h"
#include "CGraph.h"

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
        std::cout << "=======================" << std::endl;

        std::cout << "sizeof(*ptr) " << sizeof(*myParam) << " | addr " << myParam << std::endl;

        std::cout << "=======================" << std::endl;

        // std::vector<int> _list;
        // for (int i = 0; i < 10; ++i) {
        //     _list.push_back(rand() % 100000);
        // }

        // {
        //     CGRAPH_PARAM_WRITE_CODE_BLOCK(myParam)
        //     // myParam->list = _list;
        // }

        return CStatus();
    }
};
