#pragma once

#include "RenderUtils.hpp"
#include <list>
#include "ParticleGenerator.h"

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

