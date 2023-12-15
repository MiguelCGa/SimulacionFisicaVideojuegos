#pragma once

#include "Actor.h"

class RigidBody : public Actor {
public:
	RigidBody(physx::PxPhysics* ph, physx::PxScene* mScene, Vector3 pos, physx::PxActorType::Enum type, physx::PxShape* shape, double density, Vector4 color, double life_time, BoundingBox const& pos_limits);
	virtual ~RigidBody();
	
	void addForce(Vector3 const& newForce) override;
	// Returns an identicle actor
	Actor* clone() const override;
	// Initializeed the actor with said arguments
	void initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) override;

	Vector3 getPosition() const override;
	Vector3 getVelocity() const override;
	float getMass() const override;
	bool isDynamic() const;

	physx::PxRigidActor* getActor();

protected:
	float getSize() const;

	physx::PxPhysics* _gPhysics;
	physx::PxScene* _mScene;
	physx::PxShape* _shape;
	physx::PxRigidActor* _rigidActor;
	double _density;

private:
	physx::PxRigidBody* getRigidBody() const;
	physx::PxRigidActor* createRigidActor(physx::PxPhysics* gPhysics, physx::PxActorType::Enum type, Vector3 pos);
};

