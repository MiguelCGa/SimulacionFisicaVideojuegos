#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) :
	AnchoredSpringForceGenerator(k, resting_length, other->getPosition(), false),
	_other(other) {
}

bool SpringForceGenerator::updateForce(Particle* p) {
	_anchorPoint.p = _other->getPosition();
	return AnchoredSpringForceGenerator::updateForce(p);
}
