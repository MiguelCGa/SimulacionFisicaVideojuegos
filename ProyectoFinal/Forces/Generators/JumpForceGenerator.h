#pragma once
#include "../ForceGenerator.h"

class JumpForceGenerator : public ForceGenerator {
public:
	JumpForceGenerator(double jumpIntensity, double invMass, double speed);

private:
	void applyForce(Actor* p) override;

	const double _jumpIntensity, _invMass, _speed;
};