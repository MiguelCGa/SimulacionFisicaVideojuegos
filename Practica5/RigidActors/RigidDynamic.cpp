#include "RigidDynamic.h"
#include "../Random/Utils.h"

RigidDynamic::RigidDynamic(physx::PxPhysics* gPhysics, physx::PxScene* mScene, Vector3 pos, physx::PxActorType::Enum type, physx::PxShape* shape, double density, Vector4 color, double life_time, BoundingBox const& pos_limits) :
	Actor(new RenderItem(shape, _rigidDynamic = gPhysics->createRigidDynamic(physx::PxTransform(pos)), color), life_time, pos_limits),
	_gPhysics(gPhysics),
	_mScene(mScene),
	_shape(shape),
	_density(density) {

	_rigidDynamic->attachShape(*_shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*_rigidDynamic, _density);
	_mScene->addActor(*_rigidDynamic);
}

RigidDynamic::~RigidDynamic() {
	_rigidDynamic->detachShape(*_shape);
	_shape->release();
	_shape = nullptr;
	_mScene->removeActor(*_rigidDynamic);
	_rigidDynamic->release();
	_rigidDynamic = nullptr;
}


void RigidDynamic::addForce(Vector3 const& newForce) {
	_rigidDynamic->addForce(newForce);
}



Actor* RigidDynamic::clone() const {
	return new RigidDynamic(_gPhysics, _mScene, _rigidDynamic->getGlobalPose().p, _rigidDynamic->getType(), createRegularShape(_renderItem->shape->getGeometryType(), getSize()), _density, _renderItem->color, _initial_life_time, _pos_limits);
}

void RigidDynamic::initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) {
	_rigidDynamic->setGlobalPose(physx::PxTransform(_rigidDynamic->getGlobalPose().p + pos_offset, _rigidDynamic->getGlobalPose().q));
	_rigidDynamic->setLinearVelocity(_rigidDynamic->getLinearVelocity() + vel_offset);
	_initial_life_time = percentage_randomize(life_time, 20.0f);
	_life_time = _initial_life_time;
	_pos_limits = limits;
}



Vector3 RigidDynamic::getPosition() const {
	return _rigidDynamic->getGlobalPose().p;
}

Vector3 RigidDynamic::getVelocity() const {
	return _rigidDynamic->getLinearVelocity();
}

float RigidDynamic::getMass() const {
	return _rigidDynamic->getMass();
}

physx::PxRigidActor* RigidDynamic::getActor() {
	return _rigidDynamic;
}



float RigidDynamic::getSize() const {
	const auto geo = _renderItem->shape->getGeometry();
	switch (_renderItem->shape->getGeometryType()) {
	case physx::PxGeometryType::eBOX:
		return geo.box().halfExtents.y;

	case physx::PxGeometryType::eSPHERE:
		return geo.sphere().radius;
	}
}
