#include "9png.hpp"
#include "android-images.hpp"

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

    return false;
}

bool EncodeAapt9PNG(::std::string const &output, ::std::string const &injson, ::std::string const &inpng)
{
    return false;
}