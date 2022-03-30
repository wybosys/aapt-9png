#ifndef __ANDROID_IMAGES_H_INCLUDED
#define __ANDROID_IMAGES_H_INCLUDED

#define PNG_INTERNAL
#include <png.h>

extern void png_write_aapt_file(png_structp png_ptr, png_bytep data, png_size_t length);

#endif
