#include "raylib.h"
#include "graphics.h"
#include "ecs/entity.h"
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

void DrawEntity(EntityID entity) {
    TransformComponent* transform = GetComponent(entity, COMPONENT_TRANSFORM);
    MaterialComponent* material = GetComponent(entity, COMPONENT_MATERIAL);
    
    if (transform && material) {
        Vector2 pos = { transform->position.x * 50 + WINDOW_WIDTH/2, 
                       transform->position.y * 50 + WINDOW_HEIGHT/2 };
        float rotation = transform->rotation.z;
        
        // Draw rotated rectangle
        Rectangle rect = { pos.x, pos.y, 30 * transform->scale.x, 30 * transform->scale.y };
        DrawRectanglePro(rect, 
                        (Vector2){ rect.width/2, rect.height/2 },
                        rotation,
                        material->color);
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "ECS Test");
    SetupGraphics();
    SetTargetFPS(60);

    InitEntityManager();

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
            // Find last created entity and destroy it
            EntityManager* em = GetEntityManager();
            for (int i = MAX_ENTITIES-1; i >= 0; i--) {
                if (em->active[i]) {
                    DestroyEntity(em->entities[i]);
                    printf("Destroyed entity: %u\n", em->entities[i]);
                    break;
                }
            }
        }

        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Draw all entities
            EntityManager* em = GetEntityManager();
            for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
                if (em->active[i]) {
                    DrawEntity(em->entities[i]);
                }
            }

            // Debug info
            DrawRectangle(0, 0, 300, 160, Fade(BLACK, 0.8f));
            DrawFPS(10, 10);
            DrawText("Controls:", 10, 30, 20, WHITE);
            DrawText("SPACE - Create new entity", 10, 50, 20, WHITE);
            DrawText("D - Destroy last entity", 10, 70, 20, WHITE);
            DrawText("Each entity has:", 10, 90, 20, WHITE);
            DrawText("- Transform (position, rotation)", 20, 110, 20, WHITE);
            DrawText("- Material (color)", 20, 130, 20, WHITE);
            DrawText(TextFormat("Entity count: %d", em->count), 
                    10, 150, 20, WHITE);

        EndDrawing();
    }

    ShutdownEntityManager();
    CloseWindow();
    return 0;
} 