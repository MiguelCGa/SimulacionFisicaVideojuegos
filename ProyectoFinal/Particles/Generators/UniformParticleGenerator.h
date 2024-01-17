#pragma once

#include "ParticleGenerator.h"
#include "../../Random/UniformDistributionVector3.h"

class UniformParticleGenerator : public ParticleGenerator {
private:

public:
	UniformParticleGenerator(std::string name, double generation_prob, BoundingBox limits, Vector3 pos, Vector3 vel, Vector3 pos_width, Vector3 vel_width);
	UniformParticleGenerator(std::string name, double generation_prob, Vector3 pos, Vector3 vel, Vector3 pos_width, Vector3 vel_width);

	std::list<Actor*> generateParticles() override;

protected:
	Vector3 _vel_width, _pos_width;

	UniformDistributionVector3 _pos_distribution;
	UniformDistributionVector3 _vel_distribution;
};

