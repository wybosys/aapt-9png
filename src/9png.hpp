#ifndef __9PNG_H_INCLUDED
#define __9PNG_H_INCLUDED

#include <string>

class Bundle;

/**
 * @brief 解压aapt处理过的9png
 */
extern bool DecodeAapt9PNG(::std::string const &input, ::std::string const &outjson, ::std::string const &outpng);

/**
 * @brief 合并
 */
extern bool EncodeAapt9PNG(::std::string const &output, ::std::string const &injson, ::std::string const &inpng, Bundle const *bundle);

#endif
