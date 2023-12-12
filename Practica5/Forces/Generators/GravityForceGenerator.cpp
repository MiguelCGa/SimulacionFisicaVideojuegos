#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(const Vector3& g) : 
	ForceGenerator(),
	_gravity(g) {
}

void GravityForceGenerator::applyForce(Particle* p) {
	p->addForce(_gravity * p->getMass());
}

void GravityForceGenerator::setGravity(const Vector3& g) {
	_gravity = g;
}
