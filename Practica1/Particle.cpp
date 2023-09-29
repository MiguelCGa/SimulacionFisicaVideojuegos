#include "Particle.h"


Particle::Particle(Vector3 Pos, float Inverse_mass, Vector3 Vel, Vector3 Accel) :
	inverse_mass(Inverse_mass),
	damping(0.998f),
	pose(Pos), 
	vel(Vel), 
	accel(Accel),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(255, 255, 255, 1))) {

}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrate(double t) {

	if (inverse_mass <= 0.0f) return;

	pose.p += vel * t;
	vel += accel * t;
	vel *= powf(damping, t);
}