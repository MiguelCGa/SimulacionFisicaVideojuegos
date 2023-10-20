#pragma once

#include <list>

#include "RenderUtils.hpp"
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
private:
	using myDist = std::normal_distribution<>;
	class GaussianDistributionVector3 : public ParticleGenerator::DistributionVector3<myDist> {
	public:
		GaussianDistributionVector3(Vector3 const& mean, Vector3 const& dev) :
			DistributionVector3(
				myDist::param_type(mean.x, dev.x),
				myDist::param_type(mean.y, dev.y),
				myDist::param_type(mean.z, dev.z)) {
		}
	};

public:
	GaussianParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 dev_pos, Vector3 dev_vel);

	std::list<Particle*> generateParticles() override;

protected:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;

	GaussianDistributionVector3 _pos_distribution;
	GaussianDistributionVector3 _vel_distribution;
};

