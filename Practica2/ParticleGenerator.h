#pragma once

#include <iostream>
#include <list>
#include <random>

#include "RenderUtils.hpp"
#include "Particle.h"

using random_generator = std::mt19937;

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob);
	virtual ~ParticleGenerator();

	void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() = 0;

protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* _model;

	std::random_device rd;  // a seed source for the random number engine
	random_generator gen; // mersenne_twister_engine seeded with rd()

	template <typename T>
	class DistributionVector3 {
	private:
		T x, y, z;
	public:
		Vector3 operator()(random_generator gen) {
			return Vector3(x(gen), y(gen), z(gen));
		}
	};
};

