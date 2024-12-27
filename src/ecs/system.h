#ifndef SYSTEM_H
#define SYSTEM_H

#include "entity.h"
#include <stdbool.h>

typedef void (*SystemFn)(void);
typedef bool (*SystemFilter)(EntityID);

typedef struct {
    const char* name;
    SystemFn init;
    SystemFn update;
    SystemFn shutdown;
    SystemFilter filter;
    bool enabled;
} System;

typedef struct {
    System systems[MAX_COMPONENTS];
    uint32_t count;
} SystemManager;

void InitSystemManager(void);
void ShutdownSystemManager(void);
void UpdateSystems(void);

int RegisterSystem(const char* name, SystemFn init, SystemFn update, 
                  SystemFn shutdown, SystemFilter filter);
void EnableSystem(int systemId);
void DisableSystem(int systemId);

SystemManager* GetSystemManager(void);

#endif 