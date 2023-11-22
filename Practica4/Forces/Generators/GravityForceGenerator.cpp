#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : 
	ForceGenerator(-1.0),
	_gravity(g) {
}

bool GravityForceGenerator::updateForce(Particle* p) {
	p->addForce(_gravity * p->getMass());
	return isAlive();
}

void GravityForceGenerator::setGravity(const Vector3& g) {
	_gravity = g;
}
