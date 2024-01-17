#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "../RigidBody.h"
#include "Types/Firework.h"
#include "../Forces/ParticleForceRegistry.h"
#include "../Forces/Generators/GravityForceGenerator.h"
#include "../Forces/Generators/DragForceGenerator.h"
#include "../Forces/Generators/WhirlwindForceGenerator.h"
#include "../Forces/Generators/ExplosionForceGenerator.h"
#include "../Forces/Generators/ElasticRubberForceGenerator.h"
#include "../Forces/Generators/BuoyancyForceGenerator.h"
#include "../Forces/Generators/LiquidForceGenerator.h"

class ParticleSystem {
public:
	ParticleSystem(physx::PxPhysics* gPhysics, physx::PxScene* mScene);
	virtual ~ParticleSystem();

	ParticleGenerator* addParticleGenerator(ParticleGenerator* pg);
	ParticleGenerator* getParticleGenerator(std::string name);

	// Updates the system
	virtual void integrate(double t);


	// Forces

	void initializeForces(ParticleForceRegistry* pfRegistry) noexcept;
	void addForce(ForceGenerator* fg);

	std::list<Actor*>& getParticles();

protected:

	void generateParticles();
	void updateParticles(double t);

	std::list<Actor*> _particles;
	std::list<ParticleGenerator*> _particle_generators;
	std::unordered_map<std::string, ParticleGenerator*> _name_pg;

	ParticleForceRegistry* _particle_force_registry;

	unsigned int _maxElems;
};

