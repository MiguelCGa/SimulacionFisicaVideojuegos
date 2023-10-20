#pragma once

#include "RenderUtils.hpp"
#include <list>
#include "ParticleGenerator.h"



class UniformParticleGenerator : public ParticleGenerator {
private:
	class UniformDistributionVector3 {
	private:
		std::uniform_int_distribution<> x, y, z;

	public:
		UniformDistributionVector3(Vector3 const& mean, Vector3 const& width) :
			x(mean.x - width.x, mean.x + width.x),
			y(mean.y - width.y, mean.y + width.y),
			z(mean.z - width.z, mean.z + width.z) {
		}
		Vector3 operator()(random_generator gen) {
			return Vector3(x(gen), y(gen), z(gen));
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

