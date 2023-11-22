#pragma once
#include "../ForceGenerator.h"

class ExplosionForceGenerator : public ForceGenerator {
public:
	ExplosionForceGenerator(Vector3 const& origin, const double duration, const float K, const float expansion_speed = values::speed_of_sound);

	bool updateForce(Particle* p) override;

protected:
	Vector3 _origin;
	float _K, _expansion_speed, _tau;
};