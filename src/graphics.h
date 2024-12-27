#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdbool.h>
#include "raylib.h"

void SetupGraphics(void);
void SetAntiAliasing(int samples);
void SetHDR(bool enabled);

// New model loading functions
Model LoadModelSafe(const char* filename);
void UnloadModelSafe(Model model);
void DrawModelWithTransform(Model model, Vector3 position, Vector3 rotation, Vector3 scale, Color tint);

#endif 