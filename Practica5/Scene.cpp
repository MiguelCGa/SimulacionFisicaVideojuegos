#include "Scene.h"
#include <PxSceneDesc.h>
#include "callbacks.hpp"

Scene::Scene(physx::PxPhysics* gPhysics) {

	physx::PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = physx::PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = physx::PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	mScene = gPhysics->createScene(sceneDesc);
}

void Scene::simulate(float t) {
	mAccumulator += t;
	if (mAccumulator < mStepSize) return;
	mAccumulator -= mStepSize;

	mScene->simulate(t);
	mScene->fetchResults(true);
}
