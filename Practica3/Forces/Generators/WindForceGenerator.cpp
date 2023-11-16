#include "WindForceGenerator.h"


WindForceGenerator::WindForceGenerator(Vector3 const& windVelocity,  const float k1, const float k2, BoundingBox const& area) :
	ForceGenerator(-1.0),
	_windVelicity(windVelocity),
	_k1(k1),
	_k2(k2),
	_area(area) {
}

bool WindForceGenerator::updateForce(Particle* p) {
	if (!_active) return isAlive();
	if (!_area.contains(p->getPosition())) return isAlive();

	Vector3 v = (_windVelicity - p->getVelocity());
	const float drag_coef = v.normalize();
	const Vector3 dragF = _k1 * v + _k2 * drag_coef * v;

	p->addForce(dragF);

	return isAlive();
}
