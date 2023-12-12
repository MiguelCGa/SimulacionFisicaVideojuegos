#pragma once
#include "../ForceGenerator.h"
class BuoyancyForceGenerator : virtual public ForceGenerator {
public:
	BuoyancyForceGenerator(BoundingBox const& area, float d);
	~BuoyancyForceGenerator();

protected:
	void applyForce(Particle* p) override;

	float _height;
	float _volume;
	float _fluid_density;
	float _gravity;

	physx::PxTransform _pos;
	RenderItem* _item;
};

