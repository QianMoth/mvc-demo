#pragma once

#include <CGraph/CGraph>

#include "../Param/MyParam.h"

class SortQuick : public CGraph::GNode
{
  public:
    CStatus init() override
    {
        CStatus status;
        status = CGRAPH_CREATE_GPARAM(MyParam, "quickResult");
        return status;
    }

    CStatus run() override
    {
        CGraph::CGRAPH_ECHO("[%s]", this->getName().c_str());

        auto *myParam = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, "param1");

        std::vector<int> _list;
        {
            /* 对需要使用（读或写）参数的位置，加括号{}范围限定，以减少互斥等待时间 */
            CGRAPH_PARAM_READ_CODE_BLOCK(myParam);
            _list = myParam->list;
        }

        quickSort(_list, 0, _list.size() - 1);

        auto *quickResult = CGRAPH_GET_GPARAM_WITH_NO_EMPTY(MyParam, "quickResult");
        {
            CGRAPH_PARAM_WRITE_CODE_BLOCK(quickResult);
            quickResult->list = _list;
        }

        return CStatus();
    }

  private:
    void quickSort(std::vector<int> &s, int l, int r)
    {
        if (l < r) {
            int i = l;
            int j = r;
            // 拿出第一个元素, 保存到x中,第一个位置成为一个坑
            int x = s[l];
            while (i < j) {
                // 从右向左找小于x的数
                while (i < j && s[j] >= x) {
                    // 左移, 直到遇到小于等于x的数
                    j--;
                }
                if (i < j) {
                    // 将右侧找到的小于x的元素放入左侧坑中, 右侧出现一个坑
                    // 左侧元素索引后移
                    s[i++] = s[j];
                }

                // 从左向右找大于等于x的数
                while (i < j && s[i] < x) {
                    // 右移, 直到遇到大于x的数
                    i++;
                }
                if (i < j) {
                    // 将左侧找到的元素放入右侧坑中, 左侧出现一个坑
                    // 右侧元素索引向前移动
                    s[j--] = s[i];
                }
            }
            // 此时 i=j,将保存在x中的数填入坑中
            s[i] = x;
            quickSort(s, l, i - 1);  // 递归调用
            quickSort(s, i + 1, r);
        }
    }
};
