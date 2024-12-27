#include "system.h"
#include <stdio.h>
#include <string.h>

static SystemManager systemManager = {0};

void InitSystemManager(void) {
    systemManager.count = 0;
    memset(systemManager.systems, 0, sizeof(systemManager.systems));
}

void ShutdownSystemManager(void) {
    for (uint32_t i = 0; i < systemManager.count; i++) {
        if (systemManager.systems[i].shutdown) {
            systemManager.systems[i].shutdown();
        }
    }
    systemManager.count = 0;
}

void UpdateSystems(void) {
    for (uint32_t i = 0; i < systemManager.count; i++) {
        System* sys = &systemManager.systems[i];
        if (sys->enabled && sys->update) {
            sys->update();
        }
    }
}

int RegisterSystem(const char* name, SystemFn init, SystemFn update, 
                  SystemFn shutdown, SystemFilter filter) {
    if (systemManager.count >= MAX_COMPONENTS) {
        printf("Warning: Maximum systems reached!\n");
        return -1;
    }

    int id = systemManager.count++;
    System* sys = &systemManager.systems[id];
    
    sys->name = name;
    sys->init = init;
    sys->update = update;
    sys->shutdown = shutdown;
    sys->filter = filter;
    sys->enabled = true;

    if (sys->init) sys->init();
    
    return id;
}

void EnableSystem(int systemId) {
    if (systemId >= 0 && systemId < systemManager.count) {
        systemManager.systems[systemId].enabled = true;
    }
}

void DisableSystem(int systemId) {
    if (systemId >= 0 && systemId < systemManager.count) {
        systemManager.systems[systemId].enabled = false;
    }
}

SystemManager* GetSystemManager(void) {
    return &systemManager;
} 