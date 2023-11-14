#include "Particle.h"
#include "../Random/random.h"

Particle::Particle(Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color, Vector3 gravity, float damping, double life_time, BoundingBox pos_limits) :
	_mass(Mass),
	_inverse_mass((Mass <= 0.0f) ? 0.0f : 1.0f / Mass),
	_damping(damping),
	pose(Pos), 
	_vel(Vel), 
	_accel(0.0f),
	_gravity(gravity),
	_force(0.0f),
	_initial_life_time(life_time),
	_life_time(randomize_life_time(life_time)),
	_pos_limits(pos_limits),
	renderItem(new RenderItem(CreateShape(physx::PxSphereGeometry(1)), &pose, Color)) {
}

Particle::~Particle() {
	renderItem->release();
	renderItem = nullptr;
}

bool Particle::integrate(double t) {

	if (_inverse_mass <= 0.0f) { 
		clearForce();
		return isAlive();
	}

	_accel = _force * _inverse_mass;
	_vel += (_accel/* + _gravity*/) * t;
	_vel *= powf(_damping, t);
	pose.p += _vel * t;

	_life_time -= t;

	clearForce();

	return isAlive();
}

bool Particle::isAlive() const noexcept {
	return _life_time > 0.0  && _pos_limits.contains(pose.p);
}

float Particle::getMass() const noexcept {
	return _mass;
}

Particle* Particle::clone() const {
	return new Particle(pose.p, _mass, _vel, renderItem->color, _gravity, _damping, _initial_life_time, _pos_limits);
}

void Particle::initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time) {
	pose.p += pos_offset;
	_vel += vel_offset;
	_initial_life_time = life_time;
	_life_time = life_time;
}

Particle* Particle::clone_initialized(Vector3 pos_offset, Vector3 vel_offset, double life_time) const {
	Particle* copy = this->clone();
	copy->initialize(pos_offset, vel_offset, life_time);
	return copy;
}

void Particle::kill() {

}

double Particle::randomize_life_time(double life_time) {
	return std::uniform_real_distribution<>(life_time - life_time / 10.0, life_time + life_time / 10.0)(gen());
}

void Particle::addForce(Vector3 const& newForce) {
	_force += newForce;
}

void Particle::clearForce() {
	_force *= 0.0f;
}