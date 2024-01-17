#include "RigidBody.h"
#include "Random/Utils.h"

RigidBody::RigidBody(physx::PxPhysics* gPhysics, physx::PxScene* mScene, Vector3 pos, physx::PxActorType::Enum type, physx::PxShape* shape, double density, Vector4 color, double life_time, BoundingBox const& pos_limits, Vector3 velocity) :
	Actor(new RenderItem(shape, createRigidActor(gPhysics, type, pos), color), life_time, pos_limits),
	_gPhysics(gPhysics),
	_mScene(mScene),
	_shape(shape),
	_density(density) {

	_rigidActor->attachShape(*_shape);
	if (isDynamic()) physx::PxRigidBodyExt::updateMassAndInertia(*static_cast<physx::PxRigidBody*>(_rigidActor), _density);
	_mScene->addActor(*_rigidActor);
	if (isDynamic()) getRigidBody()->setLinearVelocity(velocity);
}

RigidBody::~RigidBody() {
	_rigidActor->detachShape(*_shape);
	_shape->release();
	_shape = nullptr;
	_mScene->removeActor(*_rigidActor);
	_rigidActor->release();
	_rigidActor = nullptr;
}


void RigidBody::addForce(Vector3 const& newForce) {
	if (isDynamic()) {
		auto rb = getRigidBody();
		rb->addForce(newForce);
	}
}



Actor* RigidBody::clone() const {
	return new RigidBody(_gPhysics, _mScene, _rigidActor->getGlobalPose().p, _rigidActor->getType(), createRegularShape(_renderItem->shape->getGeometryType(), getSize()), _density, _renderItem->color, _initial_life_time, _pos_limits, (isDynamic()?getRigidBody()->getLinearVelocity():Vector3(0.0f)));
}

void RigidBody::initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) {
	_rigidActor->setGlobalPose(physx::PxTransform(_rigidActor->getGlobalPose().p + pos_offset, _rigidActor->getGlobalPose().q));
	if (isDynamic()) getRigidBody()->setLinearVelocity(getRigidBody()->getLinearVelocity() + vel_offset);
	_initial_life_time = percentage_randomize(life_time, 20.0f);
	_life_time = _initial_life_time;
	_pos_limits = limits;
}



Vector3 RigidBody::getPosition() const {
	return _rigidActor->getGlobalPose().p;
}

Vector3 RigidBody::getVelocity() const {
	if (isDynamic()) return getRigidBody()->getLinearVelocity();
	return Vector3(0.0f);
}

float RigidBody::getMass() const {
	if (isDynamic()) return getRigidBody()->getMass();
	return 0.0f;
}

bool RigidBody::isDynamic() const {
	return _rigidActor->getType() == physx::PxActorType::eRIGID_DYNAMIC;
}

physx::PxRigidActor* RigidBody::getActor() {
	return _rigidActor;
}



float RigidBody::getSize() const {
	const auto geo = _renderItem->shape->getGeometry();
	switch (_renderItem->shape->getGeometryType()) {
	case physx::PxGeometryType::eBOX:
		return geo.box().halfExtents.y;

	case physx::PxGeometryType::eSPHERE:
		return geo.sphere().radius;
	}
}

physx::PxRigidBody* RigidBody::getRigidBody() const {
	if (isDynamic()) return static_cast<physx::PxRigidBody*>(_rigidActor);
	return nullptr;
}

void RigidBody::setVelocity(Vector3 vel) {
	if (isDynamic()) getRigidBody()->setLinearVelocity(vel);
}

physx::PxRigidActor* RigidBody::createRigidActor(physx::PxPhysics* gPhysics, physx::PxActorType::Enum type, Vector3 pos) {
	switch (type) {
	case physx::PxActorType::eRIGID_STATIC:
		return _rigidActor = gPhysics->createRigidStatic(physx::PxTransform(pos));
	case physx::PxActorType::eRIGID_DYNAMIC:
		return _rigidActor = gPhysics->createRigidDynamic(physx::PxTransform(pos));
	}
}
