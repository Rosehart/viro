//
//  VROFixedParticleEmitter.h
//  ViroKit
//
//  Copyright © 2018 Viro Media. All rights reserved.
//

#ifndef VROFixedParticleEmitter_h
#define VROFixedParticleEmitter_h

#include <stdio.h>
#include "VROParticleEmitter.h"

class VRODriver;
class VRONode;
class VROSurface;
class VROARSession;
class VROBillboardConstraint;

/*
 Class that inherits from VROParticleEmitter that uses the particle system to draw
 a group of fixed points, in the form of bill-boarded quads, given a vec of particle
 positions in world space.
 */
class VROFixedParticleEmitter : public VROParticleEmitter {
public:
    /*
     Constructor that creates an uninitialized emitter. To initialize this emitter before
     it can be configured / modified, call VROFixedParticleEmitter::initEmitter();
     */
    VROFixedParticleEmitter();
    virtual ~VROFixedParticleEmitter();

    /*
     Constructor that creates an initialized emitter.
     */
    VROFixedParticleEmitter(std::shared_ptr<VRODriver> driver);

    /*
     Sets the world-transform scale of all particles within this emitter.
     */
    void setParticleScale(VROVector3f scale) {
        _particleScale = scale;
    }

    void setMaxParticles(int maxParticles) {
        _maxParticles = maxParticles;
        resetEmissionCycle(true);
    }

    /*
     Sets a vector of positions representing each particle in world coordinates.
     */
    void setParticleTransforms(std::vector<VROVector4f> particlesPosition);

    /*
     Clears any existing particles from being rendered in the scene.
     */
    void forceClearParticles();

    /*
     Called as a part of the main render pass for updating transforms needed for particle rendering.
     */
    void update(const VRORenderContext &context, const VROMatrix4f &computedTransform);

    /*
     Initialize the emitter with default configurations and states.
     */
    void initEmitter(std::shared_ptr<VRODriver> driver,
                     std::shared_ptr<VROSurface> surface);
private:
    /*
     The scale upon which to apply to all particles.
     */
    VROVector3f _particleScale;

    /*
     This function updates the _particles array with the given vector of new transformation data.
     Note that the recycling of particles is also done, by resurrecting zombie particles and/or
     creating new ones to meet the demand. It also computes the boundingbox that contains all
     the points.
     */
    VROBoundingBox updateParticles(std::vector<VROVector4f> particleTransforms,
                                   const VROMatrix4f &baseTransform,
                                   const VRORenderContext &context);

    /*
     A vec of computed world transforms representing each particle..
     */
    std::vector<VROVector4f> _particleComputedPositions;

    /*
     This function updates the UBO w/ the particles in _particles.
     */
    void updateUBO(VROBoundingBox boundingBox);

    /*
     Computes the transform for the given particle with the given position, constraint
     and also updates the given boundingBox.
     */
    void computeParticleTransform(VROParticle *particle,
                                  VROVector4f position,
                                  std::shared_ptr<VROBillboardConstraint> constraint,
                                  VROBoundingBox *boundingBox,
                                  const VROMatrix4f &baseTransform,
                                  const VRORenderContext &context);

    /*
     This function adds all _particles from startIndex and on to _zombieParticles
     */
    void zombifyParticles(int startIndex);
};

#endif /* VROFixedParticleEmitter_h */
