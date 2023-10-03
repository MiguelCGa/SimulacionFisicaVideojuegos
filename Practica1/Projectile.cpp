#include "Projectile.h"
#include "constants.h"

#define MAX_REAL_SPEED 3000.0f
#define MAX_SIM_SPEED 25.0f
#define MIN_SIM_SPEED 5.0f

Projectile::Projectile(Vector3 Pos, float Inverse_mass, Vector3 Vel, Vector3 Accel) :
	Particle(Pos, Inverse_mass),
	real_inverse_mass(Inverse_mass),
	real_vel(Vel),
	real_gravity(0, values::gravity, 0) {

}

void Projectile::integrate(double t) {
	adapt_real_values();
	Particle::integrate(t);
}

void Projectile::adapt_real_velocity() {
	vel = real_vel;

	const float real_mag = real_vel.magnitude();
	if (real_mag <= MIN_SIM_SPEED) return;

	vel.normalize();
	if (real_mag >= MAX_REAL_SPEED) {
		vel *= MAX_SIM_SPEED;
		return;
	}

	vel *= MIN_SIM_SPEED + real_mag * MAX_SIM_SPEED / MAX_REAL_SPEED;
}

void Projectile::adapt_real_mass() {
	inverse_mass = real_inverse_mass * conversion_factor();
}

void Projectile::adapt_real_gravity() {
	gravity = real_gravity * (1.0f / conversion_factor());
}

void Projectile::adapt_real_values() {
	adapt_real_velocity();
	adapt_real_mass();
	adapt_real_gravity();
}

float Projectile::conversion_factor() const {
	return powf(real_vel.magnitude() / vel.magnitude(), 2.0f);
}
