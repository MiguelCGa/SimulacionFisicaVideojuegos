#pragma once
#include "../ForceGenerator.h"
class DragForceGenerator : virtual public ForceGenerator {
public:
	DragForceGenerator();
	DragForceGenerator(const float k1, const float k2);
	DragForceGenerator(const float k1, const float k2, BoundingBox const& area);

protected:
	void applyForce(Actor* p) override;

	float _k1, _k2;
};

