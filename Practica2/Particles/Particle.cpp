#include "Particle.h"

Particle::Particle(Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color, Vector3 gravity, float damping, double life_time) :
	mass(Mass),
	inverse_mass((Mass <= 0.0f) ? 0.0f : 1.0f / Mass),
	_damping(damping),
	pose(Pos), 
	_vel(Vel), 
	_accel(Vector3(0, 0, 0)),
	_gravity(gravity),
	_initial_life_time(life_time),
	_life_time(life_time),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Color)),
	_onDeath(nullptr) {
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

bool Particle::integrate(double t) {

	if (inverse_mass <= 0.0f) return _life_time > 0.0;

	pose.p += _vel * t;
	_vel += (_accel + _gravity) * t;
	_vel *= powf(_damping, t);

	_life_time -= t;

	return _life_time > 0.0;
}

bool Particle::isAlive() const {
	return _life_time > 0.0;
}

Particle* Particle::clone(Vector3 pos_offset, Vector3 vel_offset) const {
	return new Particle(pose.p + pos_offset, mass, _vel + vel_offset, renderItem->color, _gravity, _damping, _initial_life_time);
}

void Particle::setOnDeath(std::function<void(Particle*)> onDeath) {
	_onDeath = onDeath;
}

void Particle::kill() {
	if (_onDeath != nullptr) _onDeath(this);
}
