#pragma once

#include "RenderUtils.hpp"
#include "constants.h"

class Particle {
public:
	Particle(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = Vector4(255, 255, 255, 1), bool grvt = true, float damping = values::damping, double life_time = values::std_life_time);
	virtual ~Particle();

	virtual void integrate(double t);
	bool isAlive() const;

	Particle* clone(Vector3 pos_offset, Vector3 vel_offset) const;

protected:
	float mass, inverse_mass;
	float _damping;
	Vector3 _gravity;
	Vector3 _vel, _accel;
	physx::PxTransform pose;
	RenderItem* renderItem;

	double _initial_life_time, _life_time;
};

