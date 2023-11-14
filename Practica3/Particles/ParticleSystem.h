#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "Types/Firework.h"
#include "../Forces/ParticleForceRegistry.h"

class ParticleSystem {
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	// Updates the system
	virtual void integrate(double t);

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;
	ParticleForceRegistry _particle_force_registry;
	std::list<ForceGenerator*> _force_generators;
};

