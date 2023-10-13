#pragma once

#include "RenderUtils.hpp"
#include <list>
#include "Particle.h"

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob);
	virtual ~ParticleGenerator();

	void setParticle(Particle* model);
	virtual std::list<Particle*> generateParticles() const = 0;

protected:
	std::string _name;
	Vector3 _mean_pos, _mean_vel;
	double _generation_probability;
	int _num_particles;
	Particle* _model;

};

