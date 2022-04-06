#ifndef __ANDROID_PLATFROM_H_INCLUDED
#define __ANDROID_PLATFROM_H_INCLUDED

#include <cstdint>
#include <cstddef>

typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef unsigned long size_t;

typedef enum
{
    NO_ERROR = 0,
    UNKNOWN_ERROR = -1,
} status_t;

struct Res_png_9patch
{

    Res_png_9patch() : wasDeserialized(false), xDivsOffset(0),
                       yDivsOffset(0), colorsOffset(0) {}

    int8_t wasDeserialized;
    uint8_t numXDivs;
    uint8_t numYDivs;
    uint8_t numColors;

    // The offset (from the start of this structure) to the xDivs & yDivs
    // array for this 9patch. To get a pointer to this array, call
    // getXDivs or getYDivs. Note that the serialized form for 9patches places
    // the xDivs, yDivs and colors arrays immediately after the location
    // of the Res_png_9patch struct.
    uint32_t xDivsOffset;
    uint32_t yDivsOffset;

    int32_t paddingLeft, paddingRight;
    int32_t paddingTop, paddingBottom;

    enum
    {
        // The 9 patch segment is not a solid color.
        NO_COLOR = 0x00000001,

        // The 9 patch segment is completely transparent.
        TRANSPARENT_COLOR = 0x00000000
    };

    // The offset (from the start of this structure) to the colors array
    // for this 9patch.
    uint32_t colorsOffset;

    // Convert data from device representation to PNG file representation.
    void deviceToFile();
    // Convert data from PNG file representation to device representation.
    void fileToDevice();

    // Serialize/Marshall the patch data into a newly malloc-ed block.
    static void *serialize(const Res_png_9patch &patchHeader, const int32_t *xDivs,
                           const int32_t *yDivs, const uint32_t *colors);
    // Serialize/Marshall the patch data into |outData|.
    static void serialize(const Res_png_9patch &patchHeader, const int32_t *xDivs,
                          const int32_t *yDivs, const uint32_t *colors, void *outData);
    // Deserialize/Unmarshall the patch data
    static Res_png_9patch *deserialize(void *data);
    // Compute the size of the serialized data structure
    size_t serializedSize() const;

    // These tell where the next section of a patch starts.
    // For example, the first patch includes the pixels from
    // 0 to xDivs[0]-1 and the second patch includes the pixels
    // from xDivs[0] to xDivs[1]-1.
    inline int32_t *getXDivs() const
    {
        return reinterpret_cast<int32_t *>(reinterpret_cast<uintptr_t>(this) + xDivsOffset);
    }
    inline int32_t *getYDivs() const
    {
        return reinterpret_cast<int32_t *>(reinterpret_cast<uintptr_t>(this) + yDivsOffset);
    }
    inline uint32_t *getColors() const
    {
        return reinterpret_cast<uint32_t *>(reinterpret_cast<uintptr_t>(this) + colorsOffset);
    }
};

#endif
