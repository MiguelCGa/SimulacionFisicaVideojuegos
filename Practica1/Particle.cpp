#include "Particle.h"
#include "constants.h"
#include <iostream>

Particle::Particle(Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color, bool grvt) :
	inverse_mass((Mass <= 0.0f) ? 0.0f : 1.0f / Mass),
	damping((grvt)?values::damping:1.0f),
	pose(Pos), 
	vel(Vel), 
	accel(Vector3(0, 0, 0)),
	gravity(0, (grvt)?values::gravity:0, 0),
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