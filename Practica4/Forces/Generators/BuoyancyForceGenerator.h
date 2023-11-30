#pragma once
#include "../ForceGenerator.h"
class BuoyancyForceGenerator : public ForceGenerator {
public:
	BuoyancyForceGenerator(BoundingBox area, float d);
	~BuoyancyForceGenerator();

	bool updateForce(Particle* p) override;
protected:
	float _height;
	float _volume;
	float _fluid_density;
	float _gravity;

	BoundingBox _area;
	physx::PxTransform _pos;
	RenderItem* _item;
};

