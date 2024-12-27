#include "raylib.h"
#include "graphics.h"
#include "ecs/entity.h"
#include "ecs/system.h"
#include "ecs/render_system.h"
#include <stdio.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void AddTestComponents(EntityID entity) {
    // Add transform component
    TransformComponent* transform = AddComponent(entity, COMPONENT_TRANSFORM);
    if (transform) {
        transform->position = (Vector3){
            GetRandomValue(-100, 100) / 10.0f,
            GetRandomValue(-100, 100) / 10.0f,
            0
        };
        transform->scale = (Vector3){ 1.0f, 1.0f, 1.0f };
        transform->rotation = (Vector3){ 0, 0, GetRandomValue(0, 360) };
    }

    // Add material component
    MaterialComponent* material = AddComponent(entity, COMPONENT_MATERIAL);
    if (material) {
        material->color = (Color){
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            GetRandomValue(50, 255),
            255
        };
        material->hasTexture = false;
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ECS Test");
    SetupGraphics();
    SetTargetFPS(60);

    InitEntityManager();
    InitSystemManager();
    InitRenderSystem();

    // Create initial test entities
    for (int i = 0; i < 5; i++) {
        EntityID entity = CreateEntity();
        if (entity != INVALID_ENTITY) {
            AddTestComponents(entity);
        }
    }

    while (!WindowShouldClose()) {
        // Update
        if (IsKeyPressed(KEY_SPACE)) {
            EntityID newEntity = CreateEntity();
            if (newEntity != INVALID_ENTITY) {
                AddTestComponents(newEntity);
                printf("Created entity: %u\n", newEntity);
            }
        }

        if (IsKeyPressed(KEY_D)) {
            EntityManager* em = GetEntityManager();
            for (int i = MAX_ENTITIES-1; i >= 0; i--) {
                if (em->active[i]) {
                    DestroyEntity(em->entities[i]);
                    printf("Destroyed entity: %u\n", em->entities[i]);
                    break;
                }
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            
            // Update all systems (including render)
            UpdateSystems();

            // Debug info overlay
            DrawRectangle(0, 0, 300, 160, Fade(BLACK, 0.8f));
            DrawFPS(10, 10);
            DrawText("Controls:", 10, 30, 20, WHITE);
            DrawText("SPACE - Create new entity", 10, 50, 20, WHITE);
            DrawText("D - Destroy last entity", 10, 70, 20, WHITE);
            DrawText("Each entity has:", 10, 90, 20, WHITE);
            DrawText("- Transform (position, rotation)", 20, 110, 20, WHITE);
            DrawText("- Material (color)", 20, 130, 20, WHITE);
            DrawText(TextFormat("Entity count: %d", GetEntityManager()->count), 
                    10, 150, 20, WHITE);
        EndDrawing();
    }

    ShutdownSystemManager();
    ShutdownEntityManager();
    CloseWindow();
    return 0;
} 