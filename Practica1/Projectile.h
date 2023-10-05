#pragma once

#include "Particle.h"

enum ProjectileType { CannonBall, TankBullet, Bullet, LaserBeam };

class Projectile : public Particle {
public:
	Projectile(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0));
	Projectile(Vector3 Pos, Vector3 Dir, ProjectileType type);

protected:
	Vector3 get_simulated_velocity(Vector3 real_vel) const;
	float get_simulated_mass(float real_mass, Vector3 real_vel) const;
	Vector3 get_simulated_gravity(Vector3 real_gravity, Vector3 real_vel) const;
	float get_conversion_factor(Vector3 real_vel, Vector3 sim_vel) const;

	static std::vector<float> projectileSpeeds;
	static std::vector<float> projectileMasses;
	static std::vector<Vector4> projectileColors;
};

