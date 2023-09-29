#pragma once

#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, float Inverse_mass, Vector3 Vel = Vector3(0, 0, 0), Vector3 Accel = Vector3(0, 0, 0));
	virtual ~Particle();

	virtual void integrate(double t);

protected:
	float inverse_mass;
	float damping;
	Vector3 vel, accel;
	physx::PxTransform pose;
	RenderItem* renderItem;

};

