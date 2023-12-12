#pragma once
#include "../ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator {
public:
	GravityForceGenerator(const Vector3& g);


	void setGravity(const Vector3& g);
private:
	void applyForce(Particle* p) override;

	Vector3 _gravity;
};

