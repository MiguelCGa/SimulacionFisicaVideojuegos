#pragma once

#include <list>

#include "../Particle.h"
#include "../../Random/random.h"

//using namespace random;

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob);
	virtual ~ParticleGenerator();

	void setParticle(Particle* model) noexcept;
	virtual std::list<Particle*> generateParticles() = 0;

protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _max_iteration_particles;
	Particle* _model;

	std::uniform_real_distribution<> _random_probability;
};

