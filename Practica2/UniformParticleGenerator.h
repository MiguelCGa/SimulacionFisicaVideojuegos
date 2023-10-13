#pragma once

#include "RenderUtils.hpp"
#include <list>
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator {
public:
	UniformParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob);

	std::list<Particle*> generateParticles() override;

protected:

};

