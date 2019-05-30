/****************************************************************************
*****************************************************************************
****       _   _ _ _               ______             _                  ****
****      | \ | (_) |             |  ____|           (_)                 ****
****      |  \| |_| |_ _ __ ___   | |__   _ __   __ _ _ _ __   ___       ****
****      | . ` | | __| '__/ _ \  |  __| | '_ \ / _` | | '_ \ / _ \      ****
****      | |\  | | |_| | | (_) | | |____| | | | (_| | | | | |  __/      ****
****      |_| \_|_|\__|_|  \___/  |______|_| |_|\__, |_|_| |_|\___|      ****
****                                             __/ |                   ****
****                                            |___/      V 0.6.1       ****
****                                                                     ****
****                     Copyright (C) 2008 - 2011 Antonio Ni�o D�az     ****
****                                   All rights reserved.              ****
****                                                                     ****
*****************************************************************************
****************************************************************************/

/****************************************************************************
*                                                                           *
* Nitro Engine V 0.6.1 is licensed under the terms of <readme_license.txt>. *
* If you have any question, email me at <antonio_nd@hotmail.com>.           *
*                                                                           *
****************************************************************************/

#ifndef __NE_FORMATS_H__
#define __NE_FORMATS_H__

#include "NETexture.h"

/*! \file   NEFormats.h
 *  \brief  Used to convert common formats into DS formats. */

/*! @defgroup formats Format covertion functions.

	Right now, there are only functions to convert BMP images into DS textures. They support
	BMP of 4, 8, 16 (X1RGB5) and 24 bits.
	@{
*/

/*! \struct NE_BMP_HEADER
 *  \brief  Header struct for a BMP file. */
typedef struct {
	u16 type;						/* Magic identifier            */
	u32 size;                       /* File size in bytes          */
	u16 reserved1, reserved2;
	u32 offset;                     /* Offset to image data, bytes */
} PACKED NE_BMP_HEADER;

/*! \struct NE_INFO_BMP_HEADER
 *  \brief  Information struct of a BMP file. */
typedef struct {
	u32 size;						/* Header size in bytes      */
	u32 width,height;				/* Width and height of image */
	u16 planes;						/* Number of color planes   */
	u16 bits;						/* Bits per pixel            */
	u32 compression;				/* Compression type          */
	u32 imagesize;					/* Image size in bytes       */
	u32 xresolution,yresolution;	/* Pixels per meter          */
	u32 ncolors;					/* Number of colors         */
	u32 importantcolors;			/* Important colors         */
} PACKED NE_INFO_BMP_HEADER;


/*! \fn    int NE_FATMaterialTexLoadBMPtoRGBA(NE_Material * tex, char * filename, bool transpcolor);
 *  \brief Converts a bmp file in FAT to RGBA texture and loads it to a material.
 *  \param tex Material to hold the texture.
 *  \param filename Path to a bmp file in FAT. Format must be 16bit(X1RGB5) or 24 bit.
 *  \param transpcolor If true, pixel 0 color will be transparent. */
int NE_FATMaterialTexLoadBMPtoRGBA(NE_Material * tex, char * filename, bool transpcolor);

/*! \fn    int NE_FATMaterialTexLoadBMPtoRGB256(NE_Material * tex, NE_Palette * pal, char * filename, bool transpcolor);
 *  \brief Converts a bmp file in FAT to RGB256 texture and loads it in a texture and a palette struct.
 *  \param tex Material struct to hold the data.
 *  \param pal Palette struct to hold the data.
 *  \param filename Path to the bmp file. Format must be 8 or 4 bit.
 *  \param transpcolor If true, palette color 0 will be transparent. */
int NE_FATMaterialTexLoadBMPtoRGB256(NE_Material * tex, NE_Palette * pal, char * filename, bool transpcolor);

/*! \fn    int NE_MaterialTexLoadBMPtoRGBA(NE_Material * tex, void * pointer, bool transpcolor);
 *  \brief Converts a bmp file to RGBA texture and loads it to a material.
 *  \param tex Material to hold the texture.
 *  \param pointer Pointer to a bmp file in RAM. Format must be 16bit(X1RGB5) or 24 bit.
 *  \param transpcolor If true, pixel 0 color will be transparent. */
int NE_MaterialTexLoadBMPtoRGBA(NE_Material * tex, void * pointer, bool transpcolor);

/*! \fn    int NE_MaterialTexLoadBMPtoRGB256(NE_Material * tex, NE_Palette * pal, void * pointer, bool transpcolor);
 *  \brief Converts a bmp file in RAM to RGB256 texture and loads it in a texture and a palette struct.
 *  \param tex Material struct to hold the data.
 *  \param pal Palette struct to hold the data.
 *  \param pointer Pointer to the bmp file. Format must be 8 or 4 bit.
 *  \param transpcolor If true, palette color 0 will be transparent. */
int NE_MaterialTexLoadBMPtoRGB256(NE_Material * tex, NE_Palette * pal, void * pointer, bool transpcolor);

/*! @} */ //formats

#endif //__NE_FORMATS_H__
