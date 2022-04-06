#include "9png.hpp"
#include "android-images.hpp"
#include <json/json.h>
#include <fstream>

bool DecodeAapt9PNG(::std::string const &input, ::std::string const &outjson, ::std::string const &outpng)
{
    auto read_file = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, nullptr, nullptr);
    if (!read_file)
    {
        return false;
    }

    auto read_info = png_create_info_struct(read_file);
    if (!read_info)
    {
        return false;
    }

    image_info info;
    auto fp = fopen(input.c_str(), "rb");
    if (!read_png_protected(read_file, input, read_info, input, fp, &info))
    {
        png_destroy_read_struct(&read_file, &read_info, nullptr);
        fclose(fp);
        return false;
    }

    // 输出.9信息
    Json::Value root;
    ::std::ofstream stm(outjson);
    stm << root.toStyledString();
    stm.close();

    png_destroy_read_struct(&read_file, &read_info, nullptr);
    fclose(fp);
    return false;
}

bool EncodeAapt9PNG(::std::string const &output, ::std::string const &injson, ::std::string const &inpng, Bundle const *bundle)
{
    return false;
}