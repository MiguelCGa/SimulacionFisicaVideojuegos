#include "Projectile.h"


Projectile::Projectile(Vector3 Pos, float Inverse_mass, Vector3 Vel, Vector3 Accel) :
	Particle(Pos, Inverse_mass),
	real_inverse_mass(Inverse_mass),
	real_vel(Vel) {

}

void Projectile::integrate(double t) {
	adapt_real_values();
	Particle::integrate(t);
}

void Projectile::adapt_real_velocity() {
	vel = real_vel;

	const float real_mag = real_vel.magnitude();
	if (real_mag <= 5.0f) return;

	vel.normalize();
	if (real_mag >= 300000000.0f) {
		vel *= 25.0f;
		return;
	}

	vel *= 5 + real_mag * 25.0f / 300000000.0f;
}

void Projectile::adapt_real_mass() {
	inverse_mass = real_inverse_mass * (powf(vel.magnitude(), 2.0f) / powf(real_vel.magnitude(), 2.0f));
}

void Projectile::adapt_real_gravity() {

}

void Projectile::adapt_real_values() {
	adapt_real_velocity();
	adapt_real_mass();
	adapt_real_gravity();
}
