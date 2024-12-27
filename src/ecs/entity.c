#include "entity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static EntityManager manager = {0};
static EntityID nextEntityID = 1;  // 0 is reserved for INVALID_ENTITY

void InitEntityManager(void) {
    manager.count = 0;
    nextEntityID = 1;
    
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        manager.entities[i] = INVALID_ENTITY;
        manager.active[i] = false;
        
        for (int j = 0; j < COMPONENT_COUNT; j++) {
            manager.hasComponent[i][j] = false;
            manager.components[j][i] = NULL;
        }
    }
}

void ShutdownEntityManager(void) {
    // Clean up components
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.active[i]) {
            for (int j = 0; j < COMPONENT_COUNT; j++) {
                if (manager.hasComponent[i][j]) {
                    free(manager.components[j][i]);
                }
            }
        }
    }
    
    manager.count = 0;
    nextEntityID = 1;
}

EntityID CreateEntity(void) {
    if (manager.count >= MAX_ENTITIES) {
        printf("Warning: Maximum entities reached!\n");
        return INVALID_ENTITY;
    }

    EntityID newEntity = nextEntityID++;
    
    // Find first available slot
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (!manager.active[i]) {
            manager.entities[i] = newEntity;
            manager.active[i] = true;
            manager.count++;
            return newEntity;
        }
    }

    return INVALID_ENTITY;
}

void DestroyEntity(EntityID entity) {
    if (entity == INVALID_ENTITY) return;

    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.entities[i] == entity && manager.active[i]) {
            manager.entities[i] = INVALID_ENTITY;
            manager.active[i] = false;
            manager.count--;
            return;
        }
    }
}

bool IsEntityValid(EntityID entity) {
    if (entity == INVALID_ENTITY) return false;

    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.entities[i] == entity && manager.active[i]) {
            return true;
        }
    }
    return false;
}

void* AddComponent(EntityID entity, ComponentType type) {
    if (!IsEntityValid(entity) || type >= COMPONENT_COUNT) return NULL;
    
    uint32_t index = 0;
    for (; index < MAX_ENTITIES; index++) {
        if (manager.entities[index] == entity) break;
    }
    
    if (manager.hasComponent[index][type]) {
        return manager.components[type][index];
    }
    
    size_t size = 0;
    switch (type) {
        case COMPONENT_TRANSFORM:
            size = sizeof(TransformComponent);
            break;
        case COMPONENT_MESH:
            size = sizeof(MeshComponent);
            break;
        case COMPONENT_MATERIAL:
            size = sizeof(MaterialComponent);
            break;
        case COMPONENT_CAMERA:
            size = sizeof(CameraComponent);
            break;
        default:
            return NULL;
    }
    
    void* component = calloc(1, size);
    if (!component) return NULL;
    
    manager.components[type][index] = component;
    manager.hasComponent[index][type] = true;
    
    // Initialize default values
    if (type == COMPONENT_TRANSFORM) {
        TransformComponent* transform = (TransformComponent*)component;
        transform->scale = (Vector3){ 1.0f, 1.0f, 1.0f };
    }
    
    return component;
}

void* GetComponent(EntityID entity, ComponentType type) {
    if (!IsEntityValid(entity) || type >= COMPONENT_COUNT) return NULL;
    
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.entities[i] == entity && manager.hasComponent[i][type]) {
            return manager.components[type][i];
        }
    }
    
    return NULL;
}

void RemoveComponent(EntityID entity, ComponentType type) {
    if (!IsEntityValid(entity) || type >= COMPONENT_COUNT) return;
    
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.entities[i] == entity && manager.hasComponent[i][type]) {
            free(manager.components[type][i]);
            manager.components[type][i] = NULL;
            manager.hasComponent[i][type] = false;
            return;
        }
    }
}

bool HasComponent(EntityID entity, ComponentType type) {
    if (!IsEntityValid(entity) || type >= COMPONENT_COUNT) return false;
    
    for (uint32_t i = 0; i < MAX_ENTITIES; i++) {
        if (manager.entities[i] == entity) {
            return manager.hasComponent[i][type];
        }
    }
    
    return false;
}

EntityManager* GetEntityManager(void) {
    return &manager;
} 