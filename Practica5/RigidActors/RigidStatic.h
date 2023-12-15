#pragma once

#include "../Actor.h"

class RigidStatic : public Actor {
public:
	RigidStatic(physx::PxPhysics* gPhysics, physx::PxScene* mScene, Vector3 pos, physx::PxShape* shape, Vector4 color, double life_time = -1.0);
	virtual ~RigidStatic();
	
	void addForce(Vector3 const& newForce) override;
	// Returns an identicle actor
	RigidStatic* clone() const override;
	// Initializeed the actor with said arguments
	void initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) override;

	Vector3 getPosition() const override;

	physx::PxRigidActor* getActor();

protected:
	float getSize() const;

	physx::PxPhysics* _gPhysics;
	physx::PxScene* _mScene;
	physx::PxShape* _shape;
	physx::PxRigidStatic* _rigidStatic;

private:
	physx::PxRigidActor* createRigidActor(physx::PxPhysics* gPhysics, physx::PxActorType::Enum type, Vector3 pos);
};

