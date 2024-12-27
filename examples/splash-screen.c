#include "raylib.h"
#include "graphics.h"
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void) {
    // Enable MSAA 4X before window creation
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Splash Screen");
    SetupGraphics();
    SetTargetFPS(60);

    float alpha = 0.0f;
    float scale = 0.0f;
    float timer = 0.0f;
    const float FADE_SPEED = 0.02f;
    const float SCALE_SPEED = 0.03f;

    // Load custom font with larger base size and generate mipmaps
    Font font = LoadFontEx("resources/font.ttf", 128, 0, 0);
    if (!IsWindowReady()) {
        font = GetFontDefault();
    }
    
    // Enable texture filtering for smoother text
    SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
    GenTextureMipmaps(&font.texture);

    while (!WindowShouldClose() && timer < 4.0f) {
        timer += GetFrameTime();
        
        if (timer < 2.0f) {
            alpha = fminf(alpha + FADE_SPEED, 1.0f);
            scale = fminf(scale + SCALE_SPEED, 1.0f);
        }
        else if (timer > 3.0f) {
            alpha = fmaxf(alpha - FADE_SPEED, 0.0f);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            // Draw main title with sharper text
            const char* title = "Pluto Engine";
            float fontSize = 80.0f;
            Vector2 titleSize = MeasureTextEx(font, title, fontSize, 0);
            Vector2 titlePos = {
                floorf((WINDOW_WIDTH - titleSize.x) / 2),
                floorf((WINDOW_HEIGHT - titleSize.y) / 2)
            };
            DrawTextEx(font, title, titlePos, 
                      fontSize, 0,
                      Fade(RAYWHITE, alpha));

            // Draw subtitle with improved clarity
            const char* subtitle = "Based on Raylib + C";
            float subFontSize = 30.0f;
            Vector2 subSize = MeasureTextEx(font, subtitle, subFontSize, 0);
            Vector2 subPos = {
                floorf((WINDOW_WIDTH - subSize.x) / 2),
                floorf(titlePos.y + titleSize.y + 20)
            };
            DrawTextEx(font, subtitle, subPos, 
                      subFontSize, 0,
                      Fade(GRAY, alpha));

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
} 