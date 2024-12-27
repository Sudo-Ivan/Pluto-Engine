#include "raylib.h"
#include "graphics.h"
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Room Demo");
    SetupGraphics();
    SetTargetFPS(60);

    Camera3D camera = {
        .position = (Vector3){ 10.0f, 10.0f, 10.0f },
        .target = (Vector3){ 0.0f, 0.0f, 0.0f },
        .up = (Vector3){ 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    // Load 3D model
    Model model = LoadModelSafe("resources/models/3d/test.obj");
    
    float angle = 0.0f;
    float radius = 10.0f;
    Vector3 modelRotation = {0};
    Vector3 modelScale = {1.0f, 1.0f, 1.0f};
    Vector3 modelPosition = {0};

    while (!WindowShouldClose()) {
        // Update camera position
        angle += 0.01f;
        camera.position.x = radius * cosf(angle);
        camera.position.z = radius * sinf(angle);

        // Update model rotation
        modelRotation.y += 0.02f;

        BeginDrawing();
            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(10, 1.0f);
                DrawModelWithTransform(model, modelPosition, modelRotation, modelScale, WHITE);
            EndMode3D();

            DrawFPS(10, 10);
            DrawText("Press R to reset camera", 10, 30, 20, DARKGRAY);
        EndDrawing();

        // Reset camera position on R press
        if (IsKeyPressed(KEY_R)) {
            camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
            angle = 0.0f;
        }
    }

    UnloadModelSafe(model);
    CloseWindow();
    return 0;
} 