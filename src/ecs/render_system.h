#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "system.h"
#include "entity.h"

void InitRenderSystem(void);
void UpdateRenderSystem(void);
void ShutdownRenderSystem(void);
bool RenderSystemFilter(EntityID entity);

#endif 