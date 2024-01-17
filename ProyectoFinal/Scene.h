#pragma once
#include <PxPhysicsAPI.h>
#include "Forces/ForceSystem.h"
#include "Particles/ParticleSystem.h"

class Scene {
public:
	Scene(physx::PxPhysics* gPhysics, physx::PxScene* mScene);
	virtual ~Scene();

	virtual void simulate(float t);
	// Function called when a key is pressed
	virtual void keyPress(unsigned char key, const physx::PxTransform& camera);
	virtual void keyRelease(unsigned char key, const physx::PxTransform& camera);

	physx::PxPhysics* getPxPhysics();
	physx::PxScene* getPxScene();

	ForceGenerator* addForce(ForceGenerator* fg);
	ParticleSystem* addParticleSystem(ParticleSystem* fg);
	ParticleForceRegistry* getRegistry();

protected:
	void updateActors(float t);

	physx::PxPhysics* _gPhysics;
	physx::PxScene* _mScene;

	std::list<Actor*> _mActors;
	ForceSystem* _mForceSystem;
	std::list<ParticleSystem*> _mParticleSystems;
};

