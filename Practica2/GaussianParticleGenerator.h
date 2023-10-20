#pragma once

#include <list>

#include "RenderUtils.hpp"
#include "ParticleGenerator.h"

class GaussianParticleGenerator : public ParticleGenerator {
private:
	class GaussianDistributionVector3 {
	private:
		std::normal_distribution<> x, y, z;

	public:
		GaussianDistributionVector3(Vector3 const& mean, Vector3 const& dev) :
			x(mean.x, dev.x),
			y(mean.y, dev.y),
			z(mean.z, dev.z) {
		}
		Vector3 operator()(random_generator gen) {
			return Vector3(x(gen), y(gen), z(gen));
		}
	};
public:
	GaussianParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 dev_pos, Vector3 dev_vel);

	std::list<Particle*> generateParticles() override;

protected:
	Vector3 std_dev_pos, std_dev_vel;
	double std_dev_t;
};

