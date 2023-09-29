#pragma once

#include "Particle.h"

class Projectile : public Particle {
public:
	Projectile(Vector3 Pos, float Inverse_mass, Vector3 Vel = Vector3(0, 0, 0), Vector3 Accel = Vector3(0, 0, 0));

	void integrate(double t) override;

protected:
	void adapt_real_velocity();
	void adapt_real_mass();
	void adapt_real_gravity();
	void adapt_real_values();

	float real_inverse_mass;
	Vector3 real_vel;

};

