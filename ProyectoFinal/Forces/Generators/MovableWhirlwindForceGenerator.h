#pragma once
#include "WhirlwindForceGenerator.h"

class MovableWhirlwindForceGenerator : public WhirlwindForceGenerator {
public:
	MovableWhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area);
	MovableWhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area, double duration);

	void setPosition(Vector3 const& pos);
};