#pragma once
#include "../ForceGenerator.h"

class WindForceGenerator : public ForceGenerator {
public:
	WindForceGenerator(Vector3 const& windVelocity, const float k1, const float k2, BoundingBox const& area);

	bool updateForce(Particle* p) override;

protected:
	Vector3 _windVelicity;
	float _k1, _k2;
	BoundingBox _area;
};