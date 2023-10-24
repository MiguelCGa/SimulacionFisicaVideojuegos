#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "Types/Firework.h"

class ParticleSystem {
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	virtual void integrate(double t);
	ParticleGenerator* getParticleGenerator(std::string name);
	void generateFireworkSystem();

protected:
	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;

};

