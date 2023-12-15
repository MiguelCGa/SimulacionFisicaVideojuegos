#include "Actor.h"

Actor::Actor(RenderItem* renderItem, double life_time, BoundingBox pos_limits) :
	_initial_life_time(life_time),
	_life_time(life_time),
	_pos_limits(pos_limits),
	_renderItem(renderItem) {
}

Actor::~Actor() {
	_renderItem->release();
	_renderItem = nullptr;
}

Actor* Actor::clone_initialized(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) const {
	Actor* copy = this->clone();
	copy->initialize(pos_offset, vel_offset, life_time, limits);
	return copy;
}

void Actor::kill() { }

Vector3 Actor::getVelocity() const {
	return Vector3();
}

float Actor::getMass() const {
	return 0.0f;
}

float Actor::getHeight() const {
	auto geo = _renderItem->shape->getGeometry();

	switch (_renderItem->shape->getGeometryType()) {

	case physx::PxGeometryType::eBOX:
		return geo.box().halfExtents.y * 2.0f;

	case physx::PxGeometryType::eSPHERE:
		return geo.sphere().radius * 2.0f;
	}
}

float Actor::getSection() const {
	auto geo = _renderItem->shape->getGeometry();

	switch (_renderItem->shape->getGeometryType()) {

	case physx::PxGeometryType::eBOX: {
		const auto boxHE = geo.box().halfExtents;
		return boxHE.x * boxHE.z * 4.0f;
	}

	case physx::PxGeometryType::eSPHERE: {
		const auto sphereR = geo.sphere().radius;
		return sphereR * sphereR * 4.0f;
	}
	}
}

bool Actor::integrate(double t) {
	_life_time -= t;
	return isAlive();
}

bool Actor::isAlive() const {
	return (_life_time > 0.0 || _initial_life_time < 0.0) && _pos_limits.contains(getPosition());
}