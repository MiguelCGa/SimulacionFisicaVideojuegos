#include "AnchoredSpringForceGenerator.h"


AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting_length, Vector3 const& anchorPoint) :
	ForceGenerator(-1.0),
	_k(k),
	_resting_length(resting_length),
	_anchorPoint(anchorPoint) {
}

bool AnchoredSpringForceGenerator::updateForce(Particle* p) {
	
	Vector3 relative_pos_vector = (_anchorPoint - p->getPosition());
	Vector3 force;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	force = relative_pos_vector * delta_x * _k;

	p->addForce(force);

	return isAlive();
}
