#include "graphics.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>

void SetupGraphics(void) {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    SetAntiAliasing(4);
}

void SetAntiAliasing(int samples) {
    if (samples > 0) {
        SetConfigFlags(FLAG_MSAA_4X_HINT);
        SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_BILINEAR);
    }
}

void SetHDR(bool enabled) {
    if (enabled) {
        SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    }
}

Model LoadModelSafe(const char* filename) {
    Model model = LoadModel(filename);
    if (model.meshCount == 0) {
        printf("Failed to load model: %s\n", filename);
        return LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f)); // Fallback to cube
    }
    return model;
}

void UnloadModelSafe(Model model) {
    if (model.meshCount > 0) {
        UnloadModel(model);
    }
}

void DrawModelWithTransform(Model model, Vector3 position, Vector3 rotation, Vector3 scale, Color tint) {
    DrawModelEx(model, 
               position, 
               (Vector3){0.0f, 1.0f, 0.0f},  // Rotation axis (Y-axis)
               rotation.y,                    // Rotation angle (in degrees)
               scale, 
               tint);
} 