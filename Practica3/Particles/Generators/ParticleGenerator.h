#pragma once

#include <list>

#include "../Particle.h"
#include "../../Random/random.h"

#include "../../Forces/ParticleForceRegistry.h"

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, double generation_prob, Vector3 pos, Vector3 vel);
	virtual ~ParticleGenerator();

	// Sets the particle to follow as the model
	void setParticle(Particle* model) noexcept;
	// Returns a list of new generated particles
	virtual std::list<Particle*> generateParticles() = 0;

	void initializeForces(ParticleForceRegistry* pf_registry) noexcept;
	void addForce(ForceGenerator* force);
protected:
	void applyForces(Particle* p);
	Particle* createParticle(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time);

	std::string _name;

	Particle* _model;
	Vector3 _mean_pos, _mean_vel;

	// Maximum number of particles to generate in a call to generateParticles()
	int _max_iteration_particles;
	
	// Probability to generate a particle
	double _generation_probability;
	std::uniform_real_distribution<> _random_probability;

	ParticleForceRegistry* _pf_registry;
	std::vector<ForceGenerator*> _force_generators;
};

