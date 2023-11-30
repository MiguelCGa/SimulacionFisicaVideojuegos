#pragma once

#include "AnchoredSpringForceGenerator.h"

class SpringForceGenerator : public AnchoredSpringForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Particle* other);

	bool updateForce(Particle* p) override;
protected:
	Particle* _other;
};

