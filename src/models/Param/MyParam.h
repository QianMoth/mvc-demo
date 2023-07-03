#pragma once

#include <CGraph/CGraph>

struct MyParam : public CGraph::GParam
{
    CVoid reset(const CStatus &curStatus) override
    {
        // list.clear();
    }

    std::vector<int> list;
};
