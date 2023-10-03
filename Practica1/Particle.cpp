#include "Particle.h"
#include "constants.h"

Particle::Particle(Vector3 Pos, float Inverse_mass, Vector3 Vel, Vector3 Accel) :
	inverse_mass(Inverse_mass),
	damping(values::damping),
	pose(Pos), 
	vel(Vel), 
	accel(Accel),
	gravity(0, values::gravity, 0),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(255, 255, 255, 1))) {

}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrate(double t) {

	if (inverse_mass <= 0.0f) return;

	pose.p += vel * t;
	vel += accel * t + gravity * t;
	vel *= powf(damping, t);
}