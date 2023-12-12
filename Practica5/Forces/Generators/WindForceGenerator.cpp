#include "WindForceGenerator.h"


WindForceGenerator::WindForceGenerator(Vector3 const& windVelocity,  const float k1, const float k2, BoundingBox const& area) :
	WindForceGenerator(windVelocity, k1, k2, area, -1.0) {
}

WindForceGenerator::WindForceGenerator(Vector3 const& windVelocity, const float k1, const float k2, BoundingBox const& area, double duration) :
	ForceGenerator(duration, area),
	_windVelicity(windVelocity),
	_k1(k1),
	_k2(k2) {
}

void WindForceGenerator::applyForce(Particle* p) {
	Vector3 v = (_windVelicity - p->getVelocity());
	const float drag_coef = v.normalize();
	const Vector3 dragF = _k1 * v + _k2 * drag_coef * v;

	p->addForce(dragF);
}
