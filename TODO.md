# Pluto Engine TODO

## Entity Component System (ECS)
- [x] Core ECS implementation
  - [x] Entity manager
  - [x] Component manager (integrated into entity manager)
  - [x] System manager
- [x] Basic components
  - [x] Transform component
  - [x] Mesh component
  - [x] Material component
  - [ ] Collision component
  - [x] Camera component
- [ ] Component Features
  - [ ] Component serialization
  - [ ] Component cloning
  - [ ] Component dependencies
  - [ ] Component events/messaging
- [ ] Basic systems
  - [x] Render system
    - [x] 3D mesh rendering
    - [x] 2D shape rendering
    - [x] Material handling
    - [x] Camera system integration
  - [ ] Physics system
    - [ ] Collision detection
    - [ ] Physics step
    - [ ] Force application
  - [ ] Input system
    - [ ] Key mapping
    - [ ] Mouse/gamepad support
    - [ ] Input events
- [ ] ECS Optimizations
  - [ ] Component pools
  - [ ] Archetype-based storage
  - [ ] System execution order
  - [ ] Query caching
  - [ ] Parallel system execution

## Materials System
- [ ] Material management
  - [ ] Material loading (.mat files)
  - [ ] Material properties
    - [ ] Color
    - [ ] Textures
    - [ ] Shaders
    - [ ] PBR properties
  - [ ] Material instances
  - [ ] Material hot-reload
- [ ] Material editor
  - [ ] Property editor
  - [ ] Preview window
  - [ ] Texture slots
  - [ ] Shader parameters

## Documentation
- [ ] API Documentation
  - [x] Entity System API
  - [x] Component System API
  - [ ] System Manager API
- [ ] Guides
  - [x] Getting Started
  - [ ] ECS Architecture Guide
  - [ ] Component Creation Guide
  - [ ] System Implementation Guide
- [x] Examples
  - [x] ECS Test
  - [x] 3D Room Demo
  - [x] Splash Screen
  - [ ] Physics Demo
  - [ ] Full Game Demo

## Physics Engine
- [ ] Collision detection
  - [ ] AABB collision
  - [ ] Sphere collision
  - [ ] OBB collision
  - [ ] Mesh collision
- [ ] Physics simulation
  - [ ] Rigid body dynamics
  - [ ] Gravity
  - [ ] Forces and impulses
  - [ ] Constraints
- [ ] Optimization
  - [ ] Spatial partitioning
  - [ ] Broad phase collision detection
  - [ ] Narrow phase collision detection

## FPS Controller
- [ ] Camera controls
  - [ ] Mouse look
  - [ ] Head bobbing
  - [ ] Camera shake effects
- [ ] Movement
  - [ ] WASD movement
  - [ ] Jump mechanics
  - [ ] Crouch mechanics
  - [ ] Sprint mechanics
- [ ] Collision response
  - [ ] Wall sliding
  - [ ] Step up/down
  - [ ] Slope handling

## 3D Audio System
- [ ] Core audio features
  - [ ] 3D positional audio
  - [ ] Distance attenuation
  - [ ] Doppler effect
- [ ] Audio management
  - [ ] Sound pool
  - [ ] Audio streaming
  - [ ] Memory management
- [ ] Environment effects
  - [ ] Reverb zones
  - [ ] Occlusion
  - [ ] Room effects

## TCP Multiplayer
- [ ] Core networking
  - [ ] TCP server implementation
  - [ ] Client connection handling
  - [ ] Connection pooling
  - [ ] Packet serialization/deserialization
- [ ] Game state synchronization
  - [ ] Entity replication
  - [ ] State interpolation
  - [ ] Input prediction
  - [ ] Lag compensation
- [ ] Multiplayer features
  - [ ] Player join/leave handling
  - [ ] Room/lobby system
  - [ ] Chat system
  - [ ] Player authentication
- [ ] Network optimization
  - [ ] Delta compression
  - [ ] Bandwidth optimization
  - [ ] Priority-based updates
  - [ ] Anti-cheat measures

## General Improvements
- [ ] Resource management
  - [ ] Asset loading/unloading
  - [ ] Memory pooling
  - [ ] Resource caching
- [ ] Performance optimization
  - [ ] Frustum culling
  - [ ] LOD system
  - [ ] Multithreading support
- [ ] Debug tools
  - [ ] Debug rendering
  - [ ] Performance profiling
  - [ ] Memory tracking 