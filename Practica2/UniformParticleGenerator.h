#pragma once

#include <list>

#include "RenderUtils.hpp"
#include "ParticleGenerator.h"

class UniformParticleGenerator : public ParticleGenerator {
private:
	using myDist = std::uniform_int_distribution<>;
	class UniformDistributionVector3 : public ParticleGenerator::DistributionVector3<myDist> {
	public:
		UniformDistributionVector3(Vector3 const& mean, Vector3 const& width) :
			DistributionVector3(
				myDist::param_type(mean.x - width.x, mean.x + width.x),
				myDist::param_type(mean.y - width.y, mean.y + width.y),
				myDist::param_type(mean.z - width.z, mean.z + width.z)) {
		}
	};

public:
	UniformParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 pos_width, Vector3 vel_width);

	std::list<Particle*> generateParticles() override;

protected:
	Vector3 _vel_width, _pos_width;

	UniformDistributionVector3 _pos_distribution;
	UniformDistributionVector3 _vel_distribution;
};

