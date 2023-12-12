#pragma once
#include "SpringForceGenerator.h"
class ElasticRubberForceGenerator : public SpringForceGenerator {
public:
	ElasticRubberForceGenerator(double k, double resting_length, Particle* other);
protected:
	void applyForce(Particle* p) override;
};

