#pragma once

#include "RenderUtils.hpp"

class Particle {
public:
	Particle(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = Vector4(255, 255, 255, 1), bool grvt = true);
	virtual ~Particle();

	virtual void integrate(double t);

protected:
	float inverse_mass;
	float damping;
	Vector3 gravity;
	Vector3 vel, accel;
	physx::PxTransform pose;
	RenderItem* renderItem;

};

