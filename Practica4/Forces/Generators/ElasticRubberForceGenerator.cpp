#include "ElasticRubberForceGenerator.h"

ElasticRubberForceGenerator::ElasticRubberForceGenerator(double k, double resting_length, Particle* other) : 
	SpringForceGenerator(k, resting_length, other) {
}

bool ElasticRubberForceGenerator::updateForce(Particle* p) {
	if ((_other->getPosition() - p->getPosition()).magnitudeSquared() < _resting_length*_resting_length)
		return isAlive();
	return SpringForceGenerator::updateForce(p);
}
