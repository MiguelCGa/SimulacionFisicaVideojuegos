#pragma once
#include "../ForceGenerator.h"
class DragForceGenerator : virtual public ForceGenerator {
public:
	DragForceGenerator();
	DragForceGenerator(const float k1, const float k2);
	DragForceGenerator(const float k1, const float k2, BoundingBox area);
	bool updateForce(Particle* p) override;

protected:
	float _k1, _k2;
	BoundingBox _area;
};

