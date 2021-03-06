//
//  VROParticle.h
//  ViroRenderer
//
//  Copyright © 2017 Viro Media. All rights reserved.
//

#ifndef VROParticle_h
#define VROParticle_h

#include "VROMatrix4f.h"
#include "VROVector4f.h"
#include "VROVector3f.h"

/*
 Struct containing all properties relating to a single particle, such as
 life cycle spawn, transformations, color and physics states.
 */
struct VROParticle{
    // Position at which particle had spawned at, local to the particle emitter.
    VROMatrix4f spawnedLocalTransform;

    // Position at which particle had spawned at, in world transform.
    VROMatrix4f spawnedWorldTransform;

    // Current position of the particle, local to the particle emitter.
    VROMatrix4f currentLocalTransform;

    // Current position of the particle, in world transform
    VROMatrix4f currentWorldTransform;

    // True if this particle's scale, rotation and position are continously
    // affected by changes in the emitter's transform after it has been spawned.
    bool fixedToEmitter;

    // Initial values representing scale, rotation, physics and color properties;
    // These are all determined by VROParticleModifiers that have been set on the emitter.
    VROVector3f initialRotation;
    VROVector3f initialScale;
    VROVector3f initialColor;
    VROVector3f initialVelocity;
    VROVector3f initialAccel;
    VROVector3f initialAlpha;
    VROVector4f colorCurrent;

    // The amount of time that had passed for this particle, since it had spawned.
    double timeSinceSpawnedInMs;

    // The total amount of travelled distance from it's spawned location.
    double distanceTraveled;

    // The current speed at which this particle is travelling at.
    double velocity;

    // True if the particle has died but is not yet due to be de-allocated.
    // This is mainly used for recycling particles quickly and to reduce the
    // numerous number of allocations / de-allocations of particle objects.
    bool isZombie;

    // Time at which this particle was spawned at in milliseconds.
    double spawnTimeMs;

    // Time at which this particle is killed and becomes a zombie, in milliseconds.
    double killedTimeMs;

    // Duration of time a particle remains alive, in milliseconds.
    double lifePeriodMs;

    // Duration of time a particle remains a zombie before being deallocated, in milliseconds.
    double zombiePeriodMs;
};

#endif /* VROParticle_h */
