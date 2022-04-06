#include "android-platform.hpp"
#include <arpa/inet.h>
#include <cstdio>
#include <memory>

void Res_png_9patch::deviceToFile()
{
    int32_t *xDivs = getXDivs();
    for (int i = 0; i < numXDivs; i++)
    {
        xDivs[i] = htonl(xDivs[i]);
    }
    int32_t *yDivs = getYDivs();
    for (int i = 0; i < numYDivs; i++)
    {
        yDivs[i] = htonl(yDivs[i]);
    }
    paddingLeft = htonl(paddingLeft);
    paddingRight = htonl(paddingRight);
    paddingTop = htonl(paddingTop);
    paddingBottom = htonl(paddingBottom);
    uint32_t *colors = getColors();
    for (int i = 0; i < numColors; i++)
    {
        colors[i] = htonl(colors[i]);
    }
}

void Res_png_9patch::fileToDevice()
{
    int32_t *xDivs = getXDivs();
    for (int i = 0; i < numXDivs; i++)
    {
        xDivs[i] = ntohl(xDivs[i]);
    }
    int32_t *yDivs = getYDivs();
    for (int i = 0; i < numYDivs; i++)
    {
        yDivs[i] = ntohl(yDivs[i]);
    }
    paddingLeft = ntohl(paddingLeft);
    paddingRight = ntohl(paddingRight);
    paddingTop = ntohl(paddingTop);
    paddingBottom = ntohl(paddingBottom);
    uint32_t *colors = getColors();
    for (int i = 0; i < numColors; i++)
    {
        colors[i] = ntohl(colors[i]);
    }
}

size_t Res_png_9patch::serializedSize() const
{
    // The size of this struct is 32 bytes on the 32-bit target system
    // 4 * int8_t
    // 4 * int32_t
    // 3 * uint32_t
    return 32 + numXDivs * sizeof(int32_t) + numYDivs * sizeof(int32_t) + numColors * sizeof(uint32_t);
}

void *Res_png_9patch::serialize(const Res_png_9patch &patch, const int32_t *xDivs,
                                const int32_t *yDivs, const uint32_t *colors)
{
    // Use calloc since we're going to leave a few holes in the data
    // and want this to run cleanly under valgrind
    void *newData = calloc(1, patch.serializedSize());
    serialize(patch, xDivs, yDivs, colors, newData);
    return newData;
}

static void fill9patchOffsets(Res_png_9patch *patch)
{
    patch->xDivsOffset = sizeof(Res_png_9patch);
    patch->yDivsOffset = patch->xDivsOffset + (patch->numXDivs * sizeof(int32_t));
    patch->colorsOffset = patch->yDivsOffset + (patch->numYDivs * sizeof(int32_t));
}

void Res_png_9patch::serialize(const Res_png_9patch &patch, const int32_t *xDivs,
                               const int32_t *yDivs, const uint32_t *colors, void *outData)
{
    uint8_t *data = (uint8_t *)outData;
    memcpy(data, &patch.wasDeserialized, 4);   // copy  wasDeserialized, numXDivs, numYDivs, numColors
    memcpy(data + 12, &patch.paddingLeft, 16); // copy paddingXXXX
    data += 32;

    memcpy(data, xDivs, patch.numXDivs * sizeof(int32_t));
    data += patch.numXDivs * sizeof(int32_t);
    memcpy(data, yDivs, patch.numYDivs * sizeof(int32_t));
    data += patch.numYDivs * sizeof(int32_t);
    memcpy(data, colors, patch.numColors * sizeof(uint32_t));

    fill9patchOffsets(reinterpret_cast<Res_png_9patch *>(outData));
}

Res_png_9patch *Res_png_9patch::deserialize(void *inData)
{
    Res_png_9patch *patch = reinterpret_cast<Res_png_9patch *>(inData);
    patch->wasDeserialized = true;
    fill9patchOffsets(patch);

    return patch;
}
