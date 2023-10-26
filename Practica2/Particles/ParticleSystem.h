#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "Types/Firework.h"

class ParticleSystem {
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	// Updates the system
	virtual void integrate(double t);

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;

};

