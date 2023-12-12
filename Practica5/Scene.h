#pragma once

#include <PxPhysicsAPI.h>

class Scene {
public:
	Scene(physx::PxPhysics* gPhysics);

	virtual void simulate(float t);
protected:

	float mAccumulator = 0.0f;
	float mStepSize = 1.0f / 60.0f;

	physx::PxScene* mScene;
	physx::PxDefaultCpuDispatcher* gDispatcher = NULL;
	ContactReportCallback gContactReportCallback;
};

