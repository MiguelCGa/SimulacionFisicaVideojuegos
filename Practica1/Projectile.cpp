#include "Projectile.h"

#define MAX_REAL_SPEED 300000.0f
#define MAX_SIM_SPEED 25.0f
#define MIN_SIM_SPEED 7.0f

std::vector<float> Projectile::projectileSpeeds = { 250.0f, 1800.0f, 330.0f, 300000.0f };
std::vector<float> Projectile::projectileMasses = { 12.0f, 1190.0f, 0.008f, 0.001f };
std::vector<Vector4> Projectile::projectileColors =	{	Vector4(255, 0, 0, 1),
														Vector4(0, 255, 0, 1),
														Vector4(0, 0, 255, 1),
														Vector4(255, 255, 255, 1)};


Projectile::Projectile(Vector3 Pos, float Mass, Vector3 Vel) :
	Particle(
		Pos,
		get_simulated_mass(Mass, Vel),
		get_simulated_velocity(Vel)) {
	gravity = get_simulated_gravity(gravity, Vel);
}

Projectile::Projectile(Vector3 Pos, Vector3 Dir, ProjectileType type) :
	Particle(Pos,
		get_simulated_mass(projectileMasses[type], projectileSpeeds[type] * Dir),
		get_simulated_velocity(projectileSpeeds[type] * Dir),
		projectileColors[type]) {
	gravity = get_simulated_gravity(gravity, projectileSpeeds[type] * Dir);
}

Vector3 Projectile::get_simulated_velocity(Vector3 real_vel) const {
	const float real_mag = real_vel.magnitude();
	if (real_mag <= MIN_SIM_SPEED) return real_vel;
	if (real_mag >= MAX_REAL_SPEED)	return real_vel.getNormalized() * MAX_SIM_SPEED;
	return real_vel.getNormalized() * (MIN_SIM_SPEED + (real_mag * MAX_SIM_SPEED / MAX_REAL_SPEED));
}

float Projectile::get_simulated_mass(float real_mass, Vector3 real_vel) const {
	return real_mass * get_conversion_factor(real_vel, get_simulated_velocity(real_vel));
}

Vector3 Projectile::get_simulated_gravity(Vector3 real_gravity, Vector3 real_vel) const {
	return gravity * (1.0f / get_conversion_factor(real_vel, get_simulated_velocity(real_vel)));
}

float Projectile::get_conversion_factor(Vector3 real_vel, Vector3 sim_vel) const {
	return powf(real_vel.magnitude() / sim_vel.magnitude(), 2.0f);
}
