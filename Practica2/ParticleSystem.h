#pragma once

#include <list>
#include "RenderUtils.hpp"
#include "UniformParticleGenerator.h"
#include "GaussianParticleGenerator.h"

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

