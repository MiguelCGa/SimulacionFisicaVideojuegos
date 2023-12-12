#pragma once

#include "AnchoredSpringForceGenerator.h"

class SpringForceGenerator : public AnchoredSpringForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);

protected:
	void applyForce(Particle* p) override;

	Particle* _other;
};

