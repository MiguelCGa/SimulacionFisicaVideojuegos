#include "WhirlwindForceGenerator.h"


WhirlwindForceGenerator::WhirlwindForceGenerator(const float K,  const float k1, const float k2, BoundingBox const& area) :
	WindForceGenerator(Vector3(0), k1, k2, area),
	_K(K) {
}
WhirlwindForceGenerator::WhirlwindForceGenerator(const float K,  const float k1, const float k2, BoundingBox const& area, double duration) :
	WindForceGenerator(Vector3(0), k1, k2, area, duration),
	_K(K) {
}

void WhirlwindForceGenerator::applyForce(Actor* p) {

	const Vector3 q = p->getPosition();
	const Vector3 c = _area.getOrigin();
	_windVelicity = _K * Vector3(-(q.z - c.z), 50 - (q.y - c.y), (q.x - c.x));

	WindForceGenerator::applyForce(p);
}
