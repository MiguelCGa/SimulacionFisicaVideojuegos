#include "Particle.h"



Particle::Particle(Vector3 Pos, Vector3 Vel) : 
	pose(Pos), 
	vel(Vel), 
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Vector4(255, 255, 255, 1))) {

}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

void Particle::integrate(double t) {
	pose.p += vel * t;
}