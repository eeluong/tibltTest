/*
 * Version 1.0.0.2 - March 10, 2010
 *  + Added TIBLT_UNNAMED in support of compilers without default support
 *    for anonymous unions.
 *  + Added TIBLT_FMT_UNKNOWN and TIBLT_FMT_NONE enumerations to TIBLTFMT
 *    to allow standard initiatlization value indicating no valid format
 *    is selected.
 *  + Modified signature of TIBLT() to include const modifier of TIBLTPARAMS
 *    argument to explicitly indicate the structure will not be modified by
 *    TIBLT().
 *  + Added explicit inclusion of TIBLTDEF_FMT_VENDOR_ALL to all predefined
 *    formats (value of 0 doesn't change constants).
 *  + Added explicit inclusion of TIBLTDEF_FMT_YUV_601 to all YUV formats
 *    (value of 0 doesn't change constants).
 *  + Added some predefined TIBLTDEF_FMT shifts and masks for easier parsing
 *    of TIBLTFMT.
 *
 * Version 1.0.0.1 - February 16, 2010
 *  + Corrected the predefined values of TIBLT_FMT_RGBA32 and
 *    TIBLT_FMT_RGBA32_NONPREMULT to include the TIBLTDEF_FMT_ALPHA flag.
 *
 * Version 1.0 - December 9, 2009
 *
 */

#ifndef TIBLT_H
#define TIBLT_H

/* Some compilers (or compiler settings) do not support the anonymous
 * unions used in TIBLTPARAMS below.  These compilers will support this
 * construct if given a custom keyword.  The TIBLT_UNNAMED macro is used
 * below to allow addition of the keyword when necessary.  It should be
 * defined before including this header.  For example, when gcc is used with
 * a different standard than the default, such as "-std=c99":
 *
 * #define TIBLT_UNNAMED __extension__
 * #include <TIBLT.h>
 */
#ifndef TIBLT_UNNAMED
#define TIBLT_UNNAMED
#endif /* !TIBLT_UNNAMED */

/*
 * TIBLTERROR - error codes returned by TIBLT()
 */
enum TIBLTERROR_
{
  TIBLT_ERR_NONE = 0,
  TIBLT_ERR_UNKNOWN = -1,
  TIBLT_ERR_NOT_ENOUGH_MEMORY = -2,
  TIBLT_ERR_SYSTEM_RESOURCE = -3,
  TIBLT_ERR_UNSUPPORTED_BLTPARAMS_VERSION = -4,
  TIBLT_ERR_UNSUPPORTED_SURF_VERSION = -5,
  TIBLT_ERR_UNSUPPORTED_DST_FORMAT = -6,
  TIBLT_ERR_UNSUPPORTED_SRC_FORMAT = -7,
  TIBLT_ERR_UNSUPPORTED_MASK_FORMAT = -8,
  TIBLT_ERR_UNSUPPORTED_BRUSH_FORMAT = -9,
  TIBLT_ERR_UNSUPPORTED_SRC2_FORMAT = TIBLT_ERR_UNSUPPORTED_BRUSH_FORMAT,
  TIBLT_ERR_BAD_DST_RECT = -10,
  TIBLT_ERR_BAD_SRC_RECT = -11,
  TIBLT_ERR_BAD_MASK_RECT = -12,
  TIBLT_ERR_BAD_BRUSH_RECT = -13,
  TIBLT_ERR_BAD_SRC2_RECT = TIBLT_ERR_BAD_BRUSH_RECT,
  TIBLT_ERR_BAD_CLIP_RECT = -14,
  TIBLT_ERR_UNSUPPORTED_SCALE_FACTOR = -15,
  TIBLT_ERR_UNSUPPORTED_ROTATION = -16,
  TIBLT_ERR_UNSUPPORTED_CHROMA_KEY = -17,
  TIBLT_ERR_UNSUPPORTED_BLEND = -18,
  TIBLT_ERR_UNSUPPORTED_DITHER = -19,
  TIBLT_ERR_UNSUPPORTED_ROP = -20,
  TIBLT_ERR_UNSUPPORTED_SCALE_TYPE = -21,
  TIBLT_ERR_BAD_FLAGS = -22,
  TIBLT_ERR_UNSUPPORTED_FLAGS = -23,
  TIBLT_ERR_UNSUPPORTED_CONVERSION = -24,
  TIBLT_ERR_UNSUPPORTED_DST_RECT = -25,
  TIBLT_ERR_UNSUPPORTED_SRC_RECT = -26,
  TIBLT_ERR_UNSUPPORTED_MASK_RECT = -27,
  TIBLT_ERR_UNSUPPORTED_BRUSH_RECT = -28,
  TIBLT_ERR_UNSUPPORTED_SRC2_RECT = TIBLT_ERR_UNSUPPORTED_BRUSH_RECT,
  TIBLT_ERR_UNSUPPORTED_CLIP_RECT = -29,
  TIBLT_ERR_UNSUPPORTED_COMBINATION = -30,
  TIBLT_ERR_BAD_DST_POINTER = -31,
  TIBLT_ERR_BAD_SRC_POINTER = -32,
  TIBLT_ERR_BAD_MASK_POINTER = -33,
  TIBLT_ERR_BAD_BRUSH_POINTER = -34,
  TIBLT_ERR_BAD_SRC2_POINTER = TIBLT_ERR_BAD_BRUSH_POINTER
};
typedef enum TIBLTERROR_ TIBLTERROR;

/*
 * TIBLTRECT - structure used to specify rectangles in TIBLT APIs
 */
struct TIBLTRECT_
{
  int left;
  int top;
  int width;  /* negative value indicates horizontal flip */
  int height; /* negative value indicates vertical flip */
};
typedef struct TIBLTRECT_ TIBLTRECT;

/*
 * TIBLTFMT - specifies one of the supported color formats
 *
 * TIBLTFMT is constructed from the following group of bit field specifiers:
 */

/* Upper 8 bits define vendor.  Other 24 bits are vendor defined. */
#define TIBLTDEF_FMT_VENDOR_SHIFT 24
#define TIBLTDEF_FMT_VENDOR_ALL      (0x00 << TIBLTDEF_FMT_VENDOR_SHIFT)  /* Common formats */
#define TIBLTDEF_FMT_VENDOR_TI       (0x01 << TIBLTDEF_FMT_VENDOR_SHIFT)  /* Reserved for Texas Instruments */
#define TIBLTDEF_FMT_VENDOR_RESERVED (0xFF << TIBLTDEF_FMT_VENDOR_SHIFT)  /* Reserved for special codes */
#define TIBLTDEF_FMT_VENDOR_MASK (0xFF << TIBLTDEF_FMT_VENDOR_SHIFT)

/* Bits 14-15 define the color space. */
#define TIBLTDEF_FMT_CS_SHIFT 14
#define TIBLTDEF_FMT_MONO (0 << TIBLTDEF_FMT_CS_SHIFT)  /* 0x0000 */
#define TIBLTDEF_FMT_LUT  (1 << TIBLTDEF_FMT_CS_SHIFT)  /* 0x4000 */
#define TIBLTDEF_FMT_RGB  (2 << TIBLTDEF_FMT_CS_SHIFT)  /* 0x8000 */
#define TIBLTDEF_FMT_YUV  (3 << TIBLTDEF_FMT_CS_SHIFT)  /* 0xC000 */
#define TIBLTDEF_FMT_CS_MASK (3 << TIBLTDEF_FMT_CS_SHIFT)  /* 0xC000 */

/* Bits 12 and 13 are modifiers for all color spaces. */
#define TIBLTDEF_FMT_LEFT_JUSTIFIED 0x1000  /* The components are shifted left (default is shifted right). */
#define TIBLTDEF_FMT_REVERSE        0x2000  /* Order of the components is reversed. */


/*** RGB Color Space Definitions ***/

/* Bits 8, 9, 10, and 11 are modifiers for RGB formats. */
#define TIBLTDEF_FMT_ALPHA      0x0800  /* Format includes alpha. */
#define TIBLTDEF_FMT_NONPREMULT 0x0400  /* RG&B are not premultiplied by alpha */
#define TIBLTDEF_FMT_LINEAR     0x0200  /* Components are linear (sRGB) */
#define TIBLTDEF_FMT_ALPHA1     0x0100  /* Alpha component is hard-wired to 1.0 */

/* Bits 5-7 specify the container size. */
#define TIBLTDEF_FMT_CONTAINER_SHIFT 5
#define TIBLTDEF_FMT_8BIT  (0 << TIBLTDEF_FMT_CONTAINER_SHIFT)  /* 0x0000 */
#define TIBLTDEF_FMT_16BIT (1 << TIBLTDEF_FMT_CONTAINER_SHIFT)  /* 0x0020 */
#define TIBLTDEF_FMT_24BIT (2 << TIBLTDEF_FMT_CONTAINER_SHIFT)  /* 0x0040 */
#define TIBLTDEF_FMT_32BIT (3 << TIBLTDEF_FMT_CONTAINER_SHIFT)  /* 0x0060 */
#define TIBLTDEF_FMT_CONTAINER_MASK (3 << TIBLTDEF_FMT_CONTAINER_SHIFT)

/* Bits 0-4 contain the number of RG&B bits minus one. */
#define TIBLTDEF_FMT_RGBSIZEMINUS1_SHIFT 0
#define TIBLTDEF_FMT_RGBSIZEMINUS1_MASK (0x1F << TIBLTDEF_FMT_RGBSIZEMINUS1_SHIFT)


/*** YUV Color Space Defintions ***/

/* Bit 11 is a modifer for YUV formats. */
#define TIBLTDEF_FMT_YUV_STD_SHIFT 11
#define TIBLTDEF_FMT_601 (0 << TIBLTDEF_FMT_YUV_STD_SHIFT)  /* 0x0000 - ITU-R BT.601 (formerly CCIR-601) standard. */
#define TIBLTDEF_FMT_709 (1 << TIBLTDEF_FMT_YUV_STD_SHIFT)  /* 0x0800 - ITU-R BT.709 (HD) standard. */
#define TIBLTDEF_FMT_YUV_STD_MASK (1 << TIBLTDEF_FMT_YUV_STD_SHIFT)

/* Bits 9-10 determine the YUV subsampling and layout. */
#define TIBLTDEF_FMT_YUV_LAYOUT_SHIFT 9
#define TIBLTDEF_FMT_444         (0 << TIBLTDEF_FMT_YUV_LAYOUT_SHIFT) /* 0x0000 */
#define TIBLTDEF_FMT_422         (1 << TIBLTDEF_FMT_YUV_LAYOUT_SHIFT) /* 0x0200 */
#define TIBLTDEF_FMT_420_2_PLANE (2 << TIBLTDEF_FMT_YUV_LAYOUT_SHIFT) /* 0x0400 */
#define TIBLTDEF_FMT_420_3_PLANE (3 << TIBLTDEF_FMT_YUV_LAYOUT_SHIFT) /* 0x0600 */
#define TIBLTDEF_FMT_YUV_LAYOUT_MASK (3 << TIBLTDEF_FMT_YUV_LAYOUT_SHIFT)

/* Bit 8 is a modifer for 4:2:0 3 Plane. */
#define TIBLTDEF_FMT_UV_SIDE_BY_SIDE 0x0100 /* U and V planes are side-by-side (default is one after the other) */

/* The formats below are constructed from the definitions above.  However, not
   all formats possible are specified (and named) below.  The other formats
   which can be uniquely formed using the above definitions are legitimate
   formats, and may be used as well. */
enum TIBLTFMT_
{
  TIBLT_FMT_UNKNOWN = -1,
  TIBLT_FMT_NONE = TIBLT_FMT_UNKNOWN,

  /* Monochrome */
  TIBLT_FMT_MONO1 = (1 - 1) |
                    TIBLTDEF_FMT_8BIT |
                    TIBLTDEF_FMT_MONO |
                    TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_MONO2 = (2 - 1) |
                    TIBLTDEF_FMT_8BIT |
                    TIBLTDEF_FMT_MONO |
                    TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_MONO4 = (4 - 1) |
                    TIBLTDEF_FMT_8BIT |
                    TIBLTDEF_FMT_MONO |
                    TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_MONO8 = (8 - 1) |
                    TIBLTDEF_FMT_8BIT |
                    TIBLTDEF_FMT_MONO |
                    TIBLTDEF_FMT_VENDOR_ALL,

  /* Palettized (look-up-table) */
  TIBLT_FMT_LUT1         = (1 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT1_SYMBIAN = (1 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_REVERSE |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT2         = (2 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT2_SYMBIAN = (2 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_REVERSE |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT4         = (4 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT4_SYMBIAN = (4 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_REVERSE |
                           TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_LUT8         = (8 - 1) |
                           TIBLTDEF_FMT_8BIT |
                           TIBLTDEF_FMT_LUT |
                           TIBLTDEF_FMT_VENDOR_ALL,

  /* RGB */
  TIBLT_FMT_RGB12  = (12 - 1) |
                     TIBLTDEF_FMT_16BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (0):4:4:4 */
  TIBLT_FMT_1RGB12 = (12 - 1) |
                     TIBLTDEF_FMT_16BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA1 |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (15):4:4:4 */
  TIBLT_FMT_RGB15  = (15 - 1) |
                     TIBLTDEF_FMT_16BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* x:5:5:5 */
  TIBLT_FMT_RGB16  = (16 - 1) |
                     TIBLTDEF_FMT_16BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 5:6:5 */
  TIBLT_FMT_RGB24  = (24 - 1) |
                     TIBLTDEF_FMT_24BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8 */
  TIBLT_FMT_BGR24  = (24 - 1) |
                     TIBLTDEF_FMT_24BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8 */
  TIBLT_FMT_xRGB32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (0):8:8:8 */
  TIBLT_FMT_1RGB32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA1 |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (255):8:8:8 */
  TIBLT_FMT_xBGR32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (0):8:8:8 */
  TIBLT_FMT_1BGR32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_ALPHA1 |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* (255):8:8:8 */
  TIBLT_FMT_RGBx32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:(0) */
  TIBLT_FMT_RGB132 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_ALPHA1 |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:(255) */
  TIBLT_FMT_BGRx32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:(0) */
  TIBLT_FMT_BGR132 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_ALPHA1 |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:(255) */

  /* Premultiplied ARGB */
  TIBLT_FMT_ARGB12 = (12 - 1) |
                     TIBLTDEF_FMT_16BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 4:4:4:4 */
  TIBLT_FMT_ARGB24 = (16 - 1) |
                     TIBLTDEF_FMT_24BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:5:6:5 */
  TIBLT_FMT_RGBA24 = (16 - 1) |
                     TIBLTDEF_FMT_24BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 5:6:5:8 */
  TIBLT_FMT_ARGB32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:8 */
  TIBLT_FMT_ABGR32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:8 */
  TIBLT_FMT_RGBA32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:8 */
  TIBLT_FMT_BGRA32 = (24 - 1) |
                     TIBLTDEF_FMT_32BIT |
                     TIBLTDEF_FMT_RGB |
                     TIBLTDEF_FMT_ALPHA |
                     TIBLTDEF_FMT_REVERSE |
                     TIBLTDEF_FMT_LEFT_JUSTIFIED |
                     TIBLTDEF_FMT_VENDOR_ALL,             /* 8:8:8:8 */

  /* Non-premultiplied ARGB */
  TIBLT_FMT_ARGB12_NONPREMULT = (12 - 1) |
                                TIBLTDEF_FMT_16BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_ARGB15            = (15 - 1) |
                                TIBLTDEF_FMT_16BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,  /* 1:5:5:5 - "normal" format is not premultiplied */
  TIBLT_FMT_ARGB15_NONPREMULT = TIBLT_FMT_ARGB15,
  TIBLT_FMT_ARGB24_NONPREMULT = (16 - 1) |
                                TIBLTDEF_FMT_24BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_RGBA24_NONPREMULT = (16 - 1) |
                                TIBLTDEF_FMT_24BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_LEFT_JUSTIFIED |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_ARGB32_NONPREMULT = (24 - 1) |
                                TIBLTDEF_FMT_32BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_ABGR32_NONPREMULT = (24 - 1) |
                                TIBLTDEF_FMT_32BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_REVERSE |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_RGBA32_NONPREMULT = (24 - 1) |
                                TIBLTDEF_FMT_32BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_LEFT_JUSTIFIED |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_BGRA32_NONPREMULT = (24 - 1) |
                                TIBLTDEF_FMT_32BIT |
                                TIBLTDEF_FMT_RGB |
                                TIBLTDEF_FMT_ALPHA |
                                TIBLTDEF_FMT_REVERSE |
                                TIBLTDEF_FMT_LEFT_JUSTIFIED |
                                TIBLTDEF_FMT_NONPREMULT |
                                TIBLTDEF_FMT_VENDOR_ALL,

  /* YUV 4:2:2 */
  TIBLT_FMT_UYVY = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_422 |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_Y422 = TIBLT_FMT_UYVY,
  TIBLT_FMT_VYUY = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_422 |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_YUYV = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_422 |
                   TIBLTDEF_FMT_LEFT_JUSTIFIED |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_YUY2 = TIBLT_FMT_YUYV,
  TIBLT_FMT_YVYU = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_422 |
                   TIBLTDEF_FMT_LEFT_JUSTIFIED |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL,

  /* YUV 4:2:0 */
  /** 3-plane **/
  TIBLT_FMT_YV12 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_IYUV = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_I420 = TIBLT_FMT_IYUV,
  TIBLT_FMT_IMC1 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_LEFT_JUSTIFIED |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_IMC2 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_UV_SIDE_BY_SIDE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_IMC3 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_LEFT_JUSTIFIED |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_IMC4 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_3_PLANE |
                   TIBLTDEF_FMT_UV_SIDE_BY_SIDE |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  /** 2-plane **/
  TIBLT_FMT_NV12 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_2_PLANE |
                   TIBLTDEF_FMT_VENDOR_ALL,
  TIBLT_FMT_NV21 = TIBLTDEF_FMT_YUV |
                   TIBLTDEF_FMT_601 |
                   TIBLTDEF_FMT_420_2_PLANE |
                   TIBLTDEF_FMT_REVERSE |
                   TIBLTDEF_FMT_VENDOR_ALL
};
typedef enum TIBLTFMT_ TIBLTFMT;

/*
 * TIBLTSURF - this structure defines a surface as provided by the client
 *             (TIBLT does not allocate memory for surfaces).
 */
struct TIBLTSURF_
{
  unsigned int   structsize;  /* used to distinguish structure versions */
  TIBLTFMT       format;      /* color format of the surface */
  unsigned int   width;       /* width of the surface in pixels */
  unsigned int   height;      /* height of the surface in lines */
  int            orientation; /* rotation angle of the surface in degrees */
  void*          virtptr;     /* virtual pointer to the upper left corner of the surface */
  long           virtstride;  /* distance from one pixel to the pixel immediately below it in virtual space */
  unsigned long* palette;     /* only valid when format includes TIBLTDEF_FMT_LUT; specified in BGRx format
                                 (xRGB in the 32-bit, little-endian container) */
  unsigned long* physarray;   /* array of unsigned longs holding physical addresses of surface pages */
  unsigned int   physpages;   /* number of pages (entries) in the above array */
  unsigned long  pagesize;    /* size of pages in bytes (must all be the same size) */
  long           physstride;  /* distance from one pixel to the pixel immediately below it in physical space */
};
typedef struct TIBLTSURF_ TIBLTSURF;

/*
 * TIBLTFLAGS - specifies the type of BLT to be performed in the TIBLTPARAMS structure below
 */
typedef unsigned long TIBLTFLAGS;
#define TIBLT_FLAG_ROP      0x00000001 /* Use a ROP4 as specified in ROP;
                                          Mutually exclusive with TIBLT_FLAG_BLEND */
#define TIBLT_FLAG_BLEND    0x00000002 /* Use a blend as specified in blendtype;
                                          Mutually exclusive with TIBLT_FLAG_ROP */
#define TIBLT_FLAG_KEY_SRC  0x00000004 /* Enable source color/chroma key - values specified by keylow/keyhigh;
                                          Mutually exclusive with TIBLT_FLAG_KEY_DST */
#define TIBLT_FLAG_KEY_DST  0x00000008 /* Enable destination color/chroma key - values specified by keylow/keyhigh;
                                          Mutually exclusive with TIBLT_FLAG_KEY_SRC */
#define TIBLT_FLAG_DITHER   0x00000010 /* Enable dither - type specified by dithertype */
#define TIBLT_FLAG_CLIP     0x00000020 /* Enable clipping - clipping rectangle specified by cliprect;
                                          Only makes sense when scaling */
#define TIBLT_FLAG_SRCMASK  0x00000040 /* When scaling a masked copy, mask at the source instead of the destination */

/*
 * TIBLTBLENDTYPE - specifies the type of blending operation to perform; only valid when
 *                  TIBLT_FLAG_BLEND is set in the TIBLTPARAMS.flags field.
 */
typedef unsigned long TIBLTBLENDTYPE;
#define TIBLT_BLEND_GLOBAL   0x00008000 /* globalalpha used for blending */
#define TIBLT_BLEND_REMOTE   0x00004000 /* mask used for blending */
/* Porter-Duff blending equations (assuming surfaces are premultiplied by alpha when it's in the format) */
#define TIBLT_BLEND_CLEAR    0x00000000 /* dst = 0 */
#define TIBLT_BLEND_SRC      0x00000001 /* dst = src */
#define TIBLT_BLEND_SRC2     0x00000002 /* dst = src2 */
#define TIBLT_BLEND_SRCOVER  0x00000003 /* dst = src + (1 - src alpha) x src2 */
#define TIBLT_BLEND_SRC2OVER 0x00000004 /* dst = (1 - src2 alpha) x src + src2 */
#define TIBLT_BLEND_SRCIN    0x00000005 /* dst = src2 alpha x src */
#define TIBLT_BLEND_SRC2IN   0x00000006 /* dst = src alpha x src2 */
#define TIBLT_BLEND_SRCOUT   0x00000007 /* dst = (1 - src2 alpha) x src */
#define TIBLT_BLEND_SRC2OUT  0x00000008 /* dst = (1 - src alpha) x src2 */
#define TIBLT_BLEND_SRCATOP  0x00000009 /* dst = src2 alpha x src + (1 - src alpha) x src2 */
#define TIBLT_BLEND_SRC2ATOP 0x0000000A /* dst = (1 - src2 alpha) x src + src alpha x src2 */
#define TIBLT_BLEND_SRCXOR   0x0000000B /* dst = (1 - src2 alpha) x src + (1 - src alpha) x src2 */
#define TIBLT_BLEND_PLUS     0x0000000C /* dst = src + src2 */

/*
 * TIBLTDITHERTYPE - specifies the type of dithering to perform on the output
 */
enum TIBLTDITHERTYPE_
{
  TIBLT_DT_BEST = -1,       /* Use the subjective best dithering technique */
  TIBLT_DT_FASTEST = 0,     /* Use the fastest dithering technique (may be TIBLT_DT_NONE) */
  TIBLT_DT_NONE = 1,        /* No dithering (lsbs truncated) */
  TIBLT_DT_ORDERED_2x2 = 2  /* 2x2 ordered dither */
};
typedef enum TIBLTDITHERTYPE_ TIBLTDITHERTYPE;

/*
 * TIBLTSCALETYPE - specifies the type of scaling to perform
 */
enum TIBLTSCALETYPE_
{
  TIBLT_SC_BEST = -1,             /* Use the subjective best scaling technique */
  TIBLT_SC_FASTEST = 0,           /* Use the fastest scaling technique (may be TIBLT_SC_POINT_SAMPLE) */
  TIBLT_SC_POINT_SAMPLE = 1,      /* Nearest neighbor (simple, unfiltered replication and decimation) */
  TIBLT_SC_BILINEAR = 2,          /* Four nearest pixels used in linear interpolation */
  TIBLT_SC_MODIFIED_BILINEAR = 3  /* Bilinear with prescaling by power-of-two */
};
typedef enum TIBLTSCALETYPE_ TIBLTSCALETYPE;

/*
 * TIBLTPARAMS - specifies all parameters for a BLT; passed into TIBLT()
 */
struct TIBLTPARAMS_
{
  unsigned int    structsize;   /* Used for structure version checking */
  TIBLTFLAGS      flags;        /* see TIBLT_FLAG_* above */
  TIBLT_UNNAMED union
  {
     unsigned short ROP;        /* ROP4 when TIBLT_FLAG_ROP is set */
     TIBLTBLENDTYPE blendtype;  /* Type of blend when TIBLT_FLAG_BLEND is set */
  };
  TIBLTSURF*      pdst;         /* Pointer to destination surface */
  TIBLTRECT       dstrect;      /* Rectangle into which destination data is written */
  TIBLTSURF*      psrc;         /* Pointer to source surface */
  TIBLTRECT       srcrect;      /* Rectangle from which source data is read */
  unsigned long   keylow;       /* Low chroma key of range used when either TIBLT_FLAG_*KEY is set; */
                                /* Must match keyhigh for color key or if implementation does not support range; */
                                /* Format matches source */
  unsigned long   keyhigh;      /* High chroma key of range used when either TIBLT_FLAG_*KEY is set; */
                                /* Must match keylow for color key or if implementation does not support range; */
                                /* Format matches source */
  unsigned int    globalalpha;  /* Global alpha when TIBLT_FLAG_BLEND is set in flags and TIBLT_BLEND_GLOBAL is set in blendtype; */
                                /* Value must be between 0 and 255 (0 => alpha of 0.0; 255 -> alpha of 1.0) */
  TIBLTSCALETYPE  scaletype;    /* Type of scaling when source/brush rectangle is a different size from destination */
  TIBLTDITHERTYPE dithertype;   /* Type of dither technique when TIBLT_FLAG_DITHER is set */
  TIBLTRECT       cliprect;     /* Rectangle used to clip the destination when scaling and the TIBLT_FLAG_CLIP flag is set */
  TIBLTSURF*      pmask;        /* Pointer to the mask surface */
  TIBLTRECT       maskrect;     /* Rectangle from which mask data is read */
  TIBLT_UNNAMED union
  {
    TIBLTSURF*      pbrush;     /* Pointer to the brush surface */
    TIBLTSURF*      psrc2;      /* Pointer to the source 2 surface */
  };
  TIBLT_UNNAMED union
  {
    TIBLTRECT       brushrect;  /* Rectangle from which brush data is read; */
                                /* Can be larger than the brush to enable repeated brush pattern with an offset */
    TIBLTRECT       src2rect;   /* Rectangle from which source 2 data is read */
  };
};
typedef struct TIBLTPARAMS_ TIBLTPARAMS;

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* Type of the TIBLT() function, for use by dynamic loading of TIBLT libraries. */
typedef TIBLTERROR (*PTIBLT)(const TIBLTPARAMS*);

/* Pointer to the TIBLT() function, for use by dynamic loading of TIBLT libraries. */
#ifdef DECLARE_TIBLT_AS_PTR
PTIBLT TIBLT;
#else
/* Prototype of the TIBLT() function, for use by static loading of TIBLT library. */
TIBLTERROR TIBLT(const TIBLTPARAMS*);  /* The function that triggers the BLT */
#endif /* !DONT_DECLARE_TIBLT_PTR */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* TIBLT_H */

