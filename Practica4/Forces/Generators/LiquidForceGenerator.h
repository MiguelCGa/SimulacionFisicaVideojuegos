#pragma once
#include "BuoyancyForceGenerator.h"
#include "DragForceGenerator.h"
class LiquidForceGenerator :
    virtual public BuoyancyForceGenerator,
    virtual public DragForceGenerator {
public:
    LiquidForceGenerator(BoundingBox area, float d, float k1, float k2);
    bool updateForce(Particle* p) override;
};

