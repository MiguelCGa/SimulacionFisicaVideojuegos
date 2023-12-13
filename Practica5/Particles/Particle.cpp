#include "Particle.h"
#include "../Random/random.h"
#include "../Random/Utils.h"

Particle::Particle(Vector3 Pos, float Mass, Vector3 Vel, physx::PxGeometryType::Enum form, Vector4 Color, Vector3 gravity, float damping, double life_time, BoundingBox const& pos_limits) :
	Actor(new RenderItem(createRegularShape(form), &pose, Color), life_time, pos_limits),
	_mass(Mass),
	_inverse_mass((Mass <= 0.0f) ? 0.0f : 1.0f / Mass),
	_damping(damping),
	pose(Pos), 
	_vel(Vel), 
	_accel(0.0f),
	_gravity(gravity),
	_force(0.0f) {
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

	clearForce();

	return Actor::integrate(t);
}

float Particle::getMass() const noexcept {
	return _mass;
}

Vector3 Particle::getPosition() const {
	return pose.p;
}

Vector3 Particle::getVelocity() const {
	return _vel;
}

Particle* Particle::clone() const {
	return new Particle(pose.p, _mass, _vel, _renderItem->shape->getGeometryType(), _renderItem->color, _gravity, _damping, _initial_life_time, _pos_limits);
}

void Particle::initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) {
	pose.p += pos_offset;
	_vel += vel_offset;
	_initial_life_time = percentage_randomize(life_time, 20.0f);
	_life_time = _initial_life_time;
	_pos_limits = limits;
}

void Particle::addForce(Vector3 const& newForce) {
	_force += newForce;
}

void Particle::clearForce() {
	_force *= 0.0f;
}