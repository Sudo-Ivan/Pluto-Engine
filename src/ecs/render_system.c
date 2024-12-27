#include "render_system.h"
#include "raylib.h"
#include "raymath.h"

static Camera3D mainCamera = {0};
static int renderSystemId = -1;

void InitRenderSystem(void) {
    mainCamera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    mainCamera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    mainCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    mainCamera.fovy = 45.0f;
    mainCamera.projection = CAMERA_PERSPECTIVE;
    
    renderSystemId = RegisterSystem(
        "RenderSystem",
        InitRenderSystem,
        UpdateRenderSystem,
        ShutdownRenderSystem,
        RenderSystemFilter
    );
}

void UpdateRenderSystem(void) {
    EntityManager* em = GetEntityManager();
    
    // First render 3D objects
    BeginMode3D(mainCamera);
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (!em->active[i]) continue;
        EntityID entity = em->entities[i];
        
        TransformComponent* transform = GetComponent(entity, COMPONENT_TRANSFORM);
        MeshComponent* mesh = GetComponent(entity, COMPONENT_MESH);
        MaterialComponent* material = GetComponent(entity, COMPONENT_MATERIAL);

        if (transform && mesh && material && mesh->loaded) {
            DrawModel(mesh->model, 
                     transform->position,
                     1.0f, 
                     material->color);
        }
    }
    EndMode3D();
    
    // Then render 2D objects
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (!em->active[i]) continue;
        EntityID entity = em->entities[i];
        
        TransformComponent* transform = GetComponent(entity, COMPONENT_TRANSFORM);
        MaterialComponent* material = GetComponent(entity, COMPONENT_MATERIAL);
        
        // Only render 2D if it has transform and material but no mesh
        if (transform && material && !GetComponent(entity, COMPONENT_MESH)) {
            Vector2 pos = { 
                transform->position.x * 50 + GetScreenWidth()/2, 
                transform->position.y * 50 + GetScreenHeight()/2 
            };
            
            Rectangle rect = { 
                pos.x, 
                pos.y, 
                30 * transform->scale.x, 
                30 * transform->scale.y 
            };
            
            DrawRectanglePro(rect,
                (Vector2){ rect.width/2, rect.height/2 },
                transform->rotation.z,
                material->color);
        }
    }
}

void ShutdownRenderSystem(void) {
    EntityManager* em = GetEntityManager();
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (em->active[i]) {
            MeshComponent* mesh = GetComponent(em->entities[i], COMPONENT_MESH);
            if (mesh && mesh->loaded) {
                UnloadModel(mesh->model);
            }
        }
    }
}

bool RenderSystemFilter(EntityID entity) {
    return HasComponent(entity, COMPONENT_TRANSFORM) &&
           HasComponent(entity, COMPONENT_MATERIAL);
} 