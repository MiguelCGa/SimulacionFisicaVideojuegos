#pragma once

#include <list>

#include "../Particle.h"
#include "../../Random/random.h"

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, double generation_prob, Vector3 pos, Vector3 vel);
	virtual ~ParticleGenerator();

	// Sets the particle to follow as the model
	void setParticle(Particle* model) noexcept;
	// Returns a list of new generated particles
	virtual std::list<Particle*> generateParticles() = 0;

protected:
	std::string _name;

	Particle* _model;
	Vector3 _mean_pos, _mean_vel;

	// Maximum number of particles to generate in a call to generateParticles()
	int _max_iteration_particles;
	
	// Probability to generate a particle
	double _generation_probability;
	std::uniform_real_distribution<> _random_probability;
};

