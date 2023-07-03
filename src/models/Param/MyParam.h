#pragma once

#include "CGraph.h"

class MyParam : public CGraph::GParam
{
  public:
    CVoid reset(const CStatus &curStatus) override {}

    // std::vector<int> list;
};
