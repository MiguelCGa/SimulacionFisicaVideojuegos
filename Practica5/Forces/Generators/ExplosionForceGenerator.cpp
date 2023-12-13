#include "ExplosionForceGenerator.h"


ExplosionForceGenerator::ExplosionForceGenerator(Vector3 const& origin, const double  duration, const float K, const float expansion_speed) :
	ForceGenerator(duration),
	_origin(origin),
	_K(K),
	_expansion_speed(expansion_speed),
	_tau(duration/4.0f) {
}

void ExplosionForceGenerator::applyForce(Actor* p) {
	const Vector3 diff(p->getPosition() - _origin);
	const float r = diff.magnitude();
	if (r > _expansion_speed * _t) return;

	p->addForce((_K/(r*r)) * diff * exp(-_t/_tau));
}
