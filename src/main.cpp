#include "CGraph.h"
#include "models/Node/SortGenerate.h"
#include "models/Param/MyParam.h"

using namespace CGraph;

int main(int argc, char **argv)
{
    GPipelinePtr pipeline = GPipelineFactory::create();
    CStatus status;
    GElementPtr gene = nullptr;

    status += pipeline->registerGElement<SortGenerate>(&gene, {}, "Gene");
    if (!status.isOK()) {
        return 0;  // 使用时，请对所有CGraph接口的返回值做判定。本例子中省略
    }

    status += pipeline->process();

    GPipelineFactory::remove(pipeline);
    return 0;
}

/* 打印的日志内容
sizeof(*ptr) 88 | addr 0000021841D1A6E0
sizeof(*ptr) 184 | addr 0000021841D22960
sizeof(*ptr) 208 | addr 0000021841D3F060
sizeof(*ptr) 256 | addr 0000021841D1A390
sizeof(*ptr) 320 | addr 0000021841D38020
sizeof(*ptr) 360 | addr 0000021841D23E70
sizeof(*ptr) 360 | addr 0000021841D45E80
sizeof(*ptr) 360 | addr 0000021841D46A20
sizeof(*ptr) 360 | addr 0000021841D45C60
sizeof(*ptr) 360 | addr 0000021841D48720
sizeof(*ptr) 360 | addr 0000021841D4ABF0
sizeof(*ptr) 360 | addr 0000021841D4BDB0
sizeof(*ptr) 360 | addr 0000021841D4D0F0
sizeof(*ptr) 328 | addr 0000021841D4F500
sizeof(*ptr) 152 | addr 0000021841D508E0
=======================
sizeof(*ptr) 152 | addr 0000021841D508E0
sizeof(backtrace_enable_) 1 | addr 0000021841D50960 | val 0
sizeof(key_) 40 | addr 0000021841D508F8
sizeof(backtrace_) 64
sizeof(backtrace_lock_) 16
=======================
backtrace_enable_ 0 | backtrace 0
key_ param1 | key param1
=======================
sizeof(*ptr) 152 | addr 0000021841D508E0
sizeof(backtrace_enable_) 1 | addr 0000021841D50960 | val 0
sizeof(key_) 40 | addr 0000021841D508F8 | val param1
sizeof(backtrace_) 64
sizeof(backtrace_lock_) 16
=======================
sizeof(*(result->second)) 152 | addr 0000021841D508E0
=======================
[CGraph] [Mon Jul  3 16:38:03 2023] [Gene]
key param1
sizeof(*param) 152 | addr 0000021841D508E0
=======================
sizeof(*this) 224 | addr 0000021841D508E0
sizeof(backtrace_enable_) 1 | addr 0000021841D509A8 | val 123
sizeof(key_) 40 | addr 0000021841D50940 | val
sizeof(backtrace_) 64
sizeof(backtrace_lock_) 16
######### TEST FAILED #########
sizeof(*param) 152 | addr 0000021841D508E0
=======================
sizeof(*ptr) 152 | addr 0000021841D508E0
=======================
*/