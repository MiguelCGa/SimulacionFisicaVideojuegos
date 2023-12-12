#pragma once
#include "WindForceGenerator.h"

class WhirlwindForceGenerator : public WindForceGenerator {
public:
	WhirlwindForceGenerator(const float K, const float k1, const float k2, BoundingBox const& area);

private:
	void applyForce(Particle* p) override;

	float _K;
};