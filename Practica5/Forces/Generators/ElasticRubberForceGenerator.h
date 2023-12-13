#pragma once
#include "SpringForceGenerator.h"
class ElasticRubberForceGenerator : public SpringForceGenerator {
public:
	ElasticRubberForceGenerator(double k, double resting_length, Actor* other);
protected:
	void applyForce(Actor* p) override;
};

