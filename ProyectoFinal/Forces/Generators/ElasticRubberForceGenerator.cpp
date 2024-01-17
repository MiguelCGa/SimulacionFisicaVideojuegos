#include "ElasticRubberForceGenerator.h"

ElasticRubberForceGenerator::ElasticRubberForceGenerator(double k, double resting_length, Actor* other) :
	SpringForceGenerator(k, resting_length, other) {
}

void ElasticRubberForceGenerator::applyForce(Actor* p) {
	if ((_other->getPosition() - p->getPosition()).magnitudeSquared() < _resting_length*_resting_length)
		return;
	SpringForceGenerator::applyForce(p);
}
