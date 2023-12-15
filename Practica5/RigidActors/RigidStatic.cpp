#include "RigidStatic.h"
#include "../Random/Utils.h"


RigidStatic::RigidStatic(physx::PxPhysics* gPhysics, physx::PxScene* mScene, Vector3 pos, physx::PxShape* shape, Vector4 color, double life_time) :
	Actor(new RenderItem(shape, _rigidStatic = gPhysics->createRigidStatic(physx::PxTransform(pos)), color), life_time),
	_gPhysics(gPhysics),
	_mScene(mScene),
	_shape(shape) {
	_rigidStatic->attachShape(*_shape);
	_mScene->addActor(*_rigidStatic);
}

RigidStatic::~RigidStatic() {
	_rigidStatic->detachShape(*_shape);
	_shape->release();
	_shape = nullptr;
	_mScene->removeActor(*_rigidStatic);
	_rigidStatic->release();
	_rigidStatic = nullptr;
}


void RigidStatic::addForce(Vector3 const& newForce) {

}

RigidStatic* RigidStatic::clone() const {
	return new RigidStatic(_gPhysics, _mScene, _rigidStatic->getGlobalPose().p, createRegularShape(_renderItem->shape->getGeometryType(), getSize()), _renderItem->color, _initial_life_time);
}

void RigidStatic::initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) {
	_rigidStatic->setGlobalPose(physx::PxTransform(_rigidStatic->getGlobalPose().p + pos_offset, _rigidStatic->getGlobalPose().q));
	_initial_life_time = percentage_randomize(life_time, 20.0f);
	_life_time = _initial_life_time;
	_pos_limits = limits;
}



Vector3 RigidStatic::getPosition() const {
	return _rigidStatic->getGlobalPose().p;
}

physx::PxRigidActor* RigidStatic::getActor() {
	return _rigidStatic;
}



float RigidStatic::getSize() const {
	const auto geo = _renderItem->shape->getGeometry();
	switch (_renderItem->shape->getGeometryType()) {
	case physx::PxGeometryType::eBOX:
		return geo.box().halfExtents.y;

	case physx::PxGeometryType::eSPHERE:
		return geo.sphere().radius;
	}
}
