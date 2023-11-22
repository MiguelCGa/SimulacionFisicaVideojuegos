#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator {
public:
	WhirlwindForceGenerator(const float K, const float k1, const float k2, BoundingBox const& area);

	bool updateForce(Particle* p) override;

private:
	float _K;
};