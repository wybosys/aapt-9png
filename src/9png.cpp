#include "9png.hpp"
#include "android-images.hpp"
#include <json/json.h>
#include <fstream>

bool DecodeAapt9PNG(::std::string const &input, ::std::string const &outjson, ::std::string const &outpng)
{
    auto read_file = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, nullptr, nullptr);
    auto read_info = png_create_info_struct(read_file);

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

    // 输出普通png
    auto write_file = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, nullptr, nullptr);
    auto write_info = png_create_info_struct(write_file);

    info.is9Patch = false;
    write_png_protected(write_file, outpng, write_info, &info, nullptr);

    png_destroy_read_struct(&read_file, &read_info, nullptr);
    png_destroy_write_struct(&write_file, &write_info);
    fclose(fp);
    return false;
}

bool EncodeAapt9PNG(::std::string const &output, ::std::string const &injson, ::std::string const &inpng, Bundle const *bundle)
{
    return false;
}