#pragma once
#include "SpringForceGenerator.h"
class ElasticRubberForceGenerator : public SpringForceGenerator {
public:
	ElasticRubberForceGenerator(double k, double resting_length, Particle* other);
	bool updateForce(Particle* p) override;
};

