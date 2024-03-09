// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: Antonio Niño Díaz, 2008-2024
//
// This file is part of Nitro Engine

#include <NEMain.h>

#include <filesystem.h>

typedef struct {
    NE_Camera *Camera;
    NE_Model *Model;
} SceneData;

void Draw3DScene(void *arg)
{
    SceneData *Scene = arg;

    NE_CameraUse(Scene->Camera);
    NE_ModelDraw(Scene->Model);
}

int main(int argc, char *argv[])
{
    SceneData Scene = { 0 };

    irqEnable(IRQ_HBLANK);
    irqSet(IRQ_VBLANK, NE_VBLFunc);
    irqSet(IRQ_HBLANK, NE_HBLFunc);

    // Init Nitro Engine in normal 3D mode
    NE_Init3D();

    // libnds uses VRAM_C for the text console, reserve A and B only
    NE_TextureSystemReset(0, 0, NE_VRAM_AB);
    // Init console in non-3D screen
    consoleDemoInit();

    if (!nitroFSInit(NULL))
    {
        printf("nitroFSInit failed.\nPress START to exit");
        while (1)
        {
            NE_WaitForVBL(0);

            scanKeys();
            if (keysHeld() & KEY_START)
                return 0;
        }
    }

    // Allocate space for the objects we'll use
    Scene.Model = NE_ModelCreate(NE_Static);
    Scene.Camera = NE_CameraCreate();
    NE_Material *Material = NE_MaterialCreate();

    // Set coordinates for the camera
    NE_CameraSet(Scene.Camera,
                 -8, 3, 0,  // Position
                  0, 3, 0,  // Look at
                  0, 1, 0); // Up direction

    // Load mesh from the filesystem and assign it to the object "Model".
    NE_ModelLoadStaticMeshFAT(Scene.Model, "robot.bin");
    // Load a RGB texture from RAM and assign it to "Material".
    NE_MaterialTexLoadFAT(Material, NE_RGB5, 256, 256, NE_TEXGEN_TEXCOORD,
                          "texture.img.bin");

    // Assign texture to model...
    NE_ModelSetMaterial(Scene.Model, Material);

    // We set up a light and its color
    NE_LightSet(0, NE_White, -0.5, -0.5, -0.5);

    while (1)
    {
        // Wait for next frame
        NE_WaitForVBL(0);

        // Get keys information
        scanKeys();
        uint32_t keys = keysHeld();

        printf("\x1b[0;0HPad: Rotate.");

        // Rotate model using the pad
        if (keys & KEY_UP)
            NE_ModelRotate(Scene.Model, 0, 0, -2);
        if (keys & KEY_DOWN)
            NE_ModelRotate(Scene.Model, 0, 0, 2);
        if (keys & KEY_RIGHT)
            NE_ModelRotate(Scene.Model, 0, 2, 0);
        if (keys & KEY_LEFT)
            NE_ModelRotate(Scene.Model, 0, -2, 0);

        // Draw scene
        NE_ProcessArg(Draw3DScene, &Scene);
    }

    return 0;
}
