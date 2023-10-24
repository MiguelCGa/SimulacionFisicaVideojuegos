#pragma once

#include "ParticleGenerator.h"
#include "../../Random/NormalDistributionVector3.h"

class GaussianParticleGenerator : public ParticleGenerator {
public:
	GaussianParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 dev_pos, Vector3 dev_vel);

	std::list<Particle*>& generateParticles() override;

protected:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

	NormalDistributionVector3 _pos_distribution;
	NormalDistributionVector3 _vel_distribution;
};

