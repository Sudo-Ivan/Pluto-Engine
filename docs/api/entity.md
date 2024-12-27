# Entity System API

## Core Functions

### `void InitEntityManager(void)`
Initializes the entity management system with empty state. Sets count to 0 and marks all entity slots as inactive.

### `void ShutdownEntityManager(void)`
Resets the entity management system to initial state. Clears count and resets ID generation.

### `EntityID CreateEntity(void)`
Creates a new entity and returns its unique ID. Returns INVALID_ENTITY (0) if maximum entity count (10000) is reached.

### `void DestroyEntity(EntityID entity)`
Removes an entity from the system, marking its slot as available for reuse. No effect if entity is invalid.

### `bool IsEntityValid(EntityID entity)`
Checks if an entity ID exists in the system and is currently active. Returns false for INVALID_ENTITY.

### `EntityManager* GetEntityManager(void)`
Returns pointer to the global entity manager instance.

## Types

### `EntityID`
Unsigned 32-bit integer type used as unique entity identifier. 0 is reserved as INVALID_ENTITY.

### `EntityManager`
Main entity management structure containing:
- Entity ID array (max 10000)
- Active status array
- Current entity count