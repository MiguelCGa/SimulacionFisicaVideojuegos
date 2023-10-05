#include "Particle.h"
#include "constants.h"
#include <iostream>

Particle::Particle(Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color) :
	inverse_mass((Mass <= 0.0f) ? 0.0f : 1.0f / Mass),
	damping(values::damping),
	pose(Pos), 
	vel(Vel), 
	accel(Vector3(0, 0, 0)),
	gravity(0, values::gravity, 0),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Color)) {
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrate(double t) {

	if (inverse_mass <= 0.0f) return;

	pose.p += vel * t;
	vel += (accel + gravity) * t;
	vel *= powf(damping, t);
}