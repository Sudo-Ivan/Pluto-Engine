#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stdbool.h>
#include "raylib.h"
#include "raymath.h"

typedef uint32_t EntityID;
#define MAX_ENTITIES 10000
#define MAX_COMPONENTS 32
#define INVALID_ENTITY 0

// Component type IDs
typedef enum {
    COMPONENT_TRANSFORM = 0,
    COMPONENT_MESH,
    COMPONENT_MATERIAL,
    COMPONENT_CAMERA,
    COMPONENT_COUNT
} ComponentType;

// Component structures
typedef struct {
    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
} TransformComponent;

typedef struct {
    Model model;
    bool loaded;
} MeshComponent;

typedef struct {
    Color color;
    Texture2D texture;
    bool hasTexture;
} MaterialComponent;

typedef struct {
    Camera3D camera;
    bool active;
} CameraComponent;

// Entity manager
typedef struct {
    EntityID entities[MAX_ENTITIES];
    bool active[MAX_ENTITIES];
    void* components[COMPONENT_COUNT][MAX_ENTITIES];
    bool hasComponent[MAX_ENTITIES][COMPONENT_COUNT];
    uint32_t count;
} EntityManager;

// Core entity management
void InitEntityManager(void);
void ShutdownEntityManager(void);
EntityID CreateEntity(void);
void DestroyEntity(EntityID entity);
bool IsEntityValid(EntityID entity);

// Component management
void* AddComponent(EntityID entity, ComponentType type);
void* GetComponent(EntityID entity, ComponentType type);
void RemoveComponent(EntityID entity, ComponentType type);
bool HasComponent(EntityID entity, ComponentType type);

// Entity manager access
EntityManager* GetEntityManager(void);

#endif 