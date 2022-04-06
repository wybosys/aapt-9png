#include "core.hpp"
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <iostream>
#include "9png.hpp"
#include "android-bundle.hpp"

using ::std::string;

int main(int argc, char **argv)
{
    /**
     * -d 输入的 aapt.9.png 解压为 png/json
     * -c 合并 png/json 为 aapt.9.png
     * -j json描述
     * -p png图片路径
     * -m minsdk
     */

    int opt;
    bool decodedMode = false;
    string pkgpng, json, png;
    Bundle bundle;

    while ((opt = getopt(argc, argv, "d:c:j:p:m")) != -1)
    {
        switch (opt)
        {
        case 'd':
            decodedMode = true;
            pkgpng = optarg;
            break;
        case 'c':
            decodedMode = false;
            pkgpng = optarg;
            break;
        case 'j':
            json = optarg;
            break;
        case 'p':
            png = optarg;
            break;
        case 'm':
            bundle.minSdk = atoi(optarg);
            break;
        }
    }

    bool suc;
    if (decodedMode)
    {
        suc = DecodeAapt9PNG(pkgpng, json, png);
    }
    else
    {
        suc = EncodeAapt9PNG(pkgpng, json, png, &bundle);
    }

    if (!suc)
    {
        ::std::cerr << "处理失败" << ::std::endl;
        return 2;
    }

    return 0;
}
