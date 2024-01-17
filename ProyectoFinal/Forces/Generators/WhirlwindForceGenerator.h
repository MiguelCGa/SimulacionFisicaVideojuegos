#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator {
public:
	WhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area);
	WhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area, double duration);

private:
	void applyForce(Actor* p) override;

	float _K, _height;
};