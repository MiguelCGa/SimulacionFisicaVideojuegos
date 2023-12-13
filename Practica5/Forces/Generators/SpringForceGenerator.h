#pragma once

#include "AnchoredSpringForceGenerator.h"

class SpringForceGenerator : public AnchoredSpringForceGenerator {
public:
	SpringForceGenerator(double k, double resting_length, Actor* other);

protected:
	void applyForce(Actor* p) override;

	Actor* _other;
};

