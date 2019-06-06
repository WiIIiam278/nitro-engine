// SPDX-License-Identifier: MIT
//
// Copyright (c) 2008-2011, 2019, Antonio Niño Díaz
//
// This file is part of Nitro Engine

#include <NEMain.h>

#include "bmp24bit_bin.h"

NE_Material *Texture;

void Draw3DScene(void)
{
	NE_2DViewInit();
	NE_2DDrawTexturedQuad(0, 0, 128, 128, 0, Texture);
}

int main()
{
	irqEnable(IRQ_HBLANK);
	irqSet(IRQ_VBLANK, NE_VBLFunc);
	irqSet(IRQ_HBLANK, NE_HBLFunc);

	NE_Init3D();
	lcdMainOnBottom();

	Texture = NE_MaterialCreate();
	NE_MaterialTexLoadBMPtoRGBA(Texture, (void *) bmp24bit_bin, 1);

	// Wait a bit...
	scanKeys();
	NE_WaitForVBL(0);

	while (1) {
		scanKeys();
		touchPosition touch;

		NE_Process(Draw3DScene);
		NE_WaitForVBL(0);

		if (keysHeld() & KEY_TOUCH) {
			// Update stylus coordinates when screen is pressed
			touchRead(&touch);
			NE_TextureDrawingStart(Texture);
			// Draw blue pixels with no transparency
			NE_TexturePutPixelRGBA(touch.px >> 1, touch.py >> 1,
					       RGB15(0, 0, 31) | BIT(15));
			NE_TextureDrawingEnd();
		}
	}

	return 0;
}
