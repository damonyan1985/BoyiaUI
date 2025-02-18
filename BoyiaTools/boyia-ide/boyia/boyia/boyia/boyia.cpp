﻿// boyia.cpp : Boyia编译器入口
// 编译提示 : boyia.exe test1.boyia test2.boyia test3.boyia
//

#include <iostream>
#include "BoyiaRuntime.h"
#include "FileUtil.h"

// Such as execute E:\work\project\BoyiaEngine\BoyiaTools\boyia-ide\boyia\boyia\x64\Debug>boyia.exe ..\..\..\script\build.boyia
int main(int argc, char** argv)
{
    boyia::BoyiaRuntime runtime;
    runtime.init();
    if (argc <= 1) {
        std::cout << "No args in command!\n" << argc;
        return 0;
    }

    for (LInt i = 1; i < argc; i++) {
        const char* filename = argv[i];
        String path;
        // 判断是否是绝对地址，如果是相对地址，则需要拼接
        if (!FileUtil::IsAbsolutePath(_CS(filename))) {
            FileUtil::getCurrentAbsolutePath(_CS(filename), path);
        } else {
            path = _CS(filename);
        }

        std::cout << GET_STR(path) << std::endl;
        runtime.compileFile(path);
    }

    CacheVMCode(runtime.vm());

    std::cout << "Build Complete!\n" << argc;
    return 0;
}
