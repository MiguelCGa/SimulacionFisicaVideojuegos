#include "GravityForceGenerator.h"
#include "JumpForceGenerator.h"

JumpForceGenerator::JumpForceGenerator(double jumpIntensity, double invMass, double speed) :
	ForceGenerator(0.1),
	_jumpIntensity(jumpIntensity),
	_invMass(invMass), 
	_speed(speed) {
}

void JumpForceGenerator::applyForce(Actor* p) {
	p->addForce(Vector3(0, _jumpIntensity * _invMass - _speed, 0));
}