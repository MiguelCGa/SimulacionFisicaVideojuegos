#pragma once
#include "../ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator {
public:
	GravityForceGenerator(const Vector3& g);

	bool updateForce(Particle* p) override;

	void setGravity(const Vector3& g);
private:
	Vector3 _gravity;
};

