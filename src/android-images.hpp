#ifndef __ANDROID_IMAGES_H_INCLUDED
#define __ANDROID_IMAGES_H_INCLUDED

#include "android-platform.hpp"

#define PNG_INTERNAL
#include <png.h>

struct image_info;

extern void read_png(const char *imageName,
                     png_structp read_ptr, png_infop read_info,
                     image_info *outImageInfo);

extern status_t do_9patch(const char *imageName, image_info *image);

extern status_t get_horizontal_ticks(
    png_bytep row, int width, bool transparent, bool required,
    int32_t *outLeft, int32_t *outRight, const char **outError,
    uint8_t *outDivs, bool multipleAllowed);

extern status_t get_horizontal_layout_bounds_ticks(
    png_bytep row, int width, bool transparent, bool required,
    int32_t *outLeft, int32_t *outRight, const char **outError);

extern status_t get_vertical_ticks(
    png_bytepp rows, int offset, int height, bool transparent, bool required,
    int32_t *outTop, int32_t *outBottom, const char **outError,
    uint8_t *outDivs, bool multipleAllowed);

extern status_t get_vertical_layout_bounds_ticks(
    png_bytepp rows, int offset, int height, bool transparent, bool required,
    int32_t *outTop, int32_t *outBottom, const char **outError);

extern void find_max_opacity(png_byte **rows,
                             int startX, int startY, int endX, int endY, int dX, int dY,
                             int *out_inset);

extern uint8_t max_alpha_over_row(png_byte *row, int startX, int endX);

extern uint8_t max_alpha_over_col(png_byte **rows, int offsetX, int startY, int endY);

extern void get_outline(image_info *image);

extern uint32_t get_color(
    png_bytepp rows, int left, int top, int right, int bottom);

extern uint32_t get_color(image_info *image, int hpatch, int vpatch);

extern int tick_type(png_bytep p, bool transparent, const char **outError);

extern void select_patch(
    int which, int front, int back, int size, int *start, int *end);

extern uint8_t max_alpha_over_row(png_byte *row, int startX, int endX);

extern void checkNinePatchSerialization(Res_png_9patch *inPatch, void *data);

extern void dump_image(int w, int h, png_bytepp rows, int color_type);

extern void analyze_image(const char *imageName, image_info &imageInfo, int grayscaleTolerance,
                          png_colorp rgbPalette, png_bytep alphaPalette,
                          int *paletteEntries, bool *hasTransparency, int *colorType,
                          png_bytepp outRows);

extern void write_png(const char *imageName,
                      png_structp write_ptr, png_infop write_info,
                      image_info &imageInfo, int grayscaleTolerance);

#endif
