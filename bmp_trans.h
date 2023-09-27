#ifndef __BMP_TRANS_H__
#define __BMP_TRANS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct
{
    char bfType[2];         // 标识，就是"BM"二字
    uint32_t bfSize;        // 整个BMP文件的大小
    uint32_t bfReserved;    // 保留字，没用
    uint32_t bfOffBits;     // 偏移数，即 位图文件头+位图信息头+调色板 的大小
}bitmap_file_info_t;

typedef struct
{
    uint32_t biSize;            // 位图信息头的大小，为40
    uint32_t biWidth;           // 位图的宽度，单位是像素
    uint32_t biHeight;          // 位图的高度，单位是像素
    uint16_t biPlanes;          // 固定值1
    uint16_t biBitCount;        // 每个像素的位数，1555就是16，888就是24
    uint32_t biCompression;     // 压缩方式，BI_RGB(0)为不压缩
    uint32_t biSizeImage;       // 位图全部像素占用的字节数，BI_RGB时可设为0
    uint32_t biXPelsPerMeter;   // 水平分辨率(像素/米)
    uint32_t biYPelsPerMeter;   // 垂直分辨率(像素/米)
    uint32_t biClrUsed;         // 位图使用的颜色数，如果为0，则颜色数为2的biBitCount次方
    uint32_t biClrImportant;    // 重要的颜色数，0代表所有颜色都重要
}bitmap_image_info_t;

uint8_t *bitmap_file_read(char *filename, bitmap_file_info_t *bitmap_file, bitmap_image_info_t *bitmap_image);
uint16_t *rgb888_to_argb1555(uint8_t *in_buf, uint64_t in_len, uint32_t w, uint32_t h);
uint8_t *rgb888_to_argb1111(uint8_t *in_buf, uint64_t in_len, uint32_t w, uint32_t h);
uint16_t *string_to_argb1555(char *ttf_path, char *str, uint32_t font_size, uint32_t *w, uint32_t *h);
int bitmap_file_write(char *filename, bitmap_file_info_t bitmap_file, bitmap_image_info_t bitmap_image, uint8_t *buf);

#ifdef __cplusplus
}
#endif

#endif