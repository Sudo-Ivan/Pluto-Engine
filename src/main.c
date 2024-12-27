#include "raylib.h"
#include "graphics.h"
#include "ecs/entity.h"
#include "ecs/system.h"
#include "ecs/render_system.h"
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void CreateGameObject(Vector3 position) {
    EntityID entity = CreateEntity();
    if (entity == INVALID_ENTITY) return;

    // Add transform
    TransformComponent* transform = AddComponent(entity, COMPONENT_TRANSFORM);
    if (transform) {
        transform->position = position;
        transform->scale = (Vector3){ 1.0f, 1.0f, 1.0f };
    }

    // Add mesh (placeholder)
    MeshComponent* mesh = AddComponent(entity, COMPONENT_MESH);
    if (mesh) {
        mesh->loaded = false;  // Will be loaded by render system
    }

    // Add material
    MaterialComponent* material = AddComponent(entity, COMPONENT_MATERIAL);
    if (material) {
        material->color = RED;
        material->hasTexture = false;
    }

    printf("Created game object with ID: %u\n", entity);
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Game Engine");
    SetupGraphics();
    SetTargetFPS(60);

    InitEntityManager();
    InitSystemManager();
    InitRenderSystem();

    // Create initial game objects
    CreateGameObject((Vector3){ 0, 0, 0 });
    CreateGameObject((Vector3){ 2, 0, 0 });
    CreateGameObject((Vector3){ -2, 0, 0 });

    while (!WindowShouldClose()) {
        UpdateSystems();  // This will call all registered systems

        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            CreateGameObject((Vector3){
                GetRandomValue(-5, 5),
                GetRandomValue(-5, 5),
                0
            });
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Debug info
            DrawFPS(10, 10);
            DrawText("Press SPACE to create game object", 10, 30, 20, DARKGRAY);
            DrawText(TextFormat("Active objects: %d", GetEntityManager()->count), 
                    10, 50, 20, DARKGRAY);

        EndDrawing();
    }

    ShutdownEntityManager();
    CloseWindow();
    return 0;
} 