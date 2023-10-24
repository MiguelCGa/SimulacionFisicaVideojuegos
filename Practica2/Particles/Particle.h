#pragma once

#include "../RenderUtils.hpp"
#include "../constants.h"
#include <functional>

class Particle {
public:
	Particle(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = Vector4(255, 255, 255, 1), Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time);
	virtual ~Particle();

	virtual bool integrate(double t);
	bool isAlive() const;

	virtual Particle* clone(Vector3 pos_offset, Vector3 vel_offset) const;

	void setOnDeath(std::function<void(Particle*)> onDeath);

	void kill();

protected:
	float mass, inverse_mass;
	float _damping;
	Vector3 _gravity;
	Vector3 _vel, _accel;
	physx::PxTransform pose;
	RenderItem* renderItem;

	double _initial_life_time, _life_time;

	std::function<void(Particle*)> _onDeath;
};

