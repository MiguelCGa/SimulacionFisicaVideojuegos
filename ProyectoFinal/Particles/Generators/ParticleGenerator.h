#pragma once

#include <list>

#include "../../Actor.h"
#include "../../Random/random.h"

#include "../../Forces/ParticleForceRegistry.h"

class ParticleGenerator {
public:
	ParticleGenerator(std::string name, double generation_prob, BoundingBox limits, Vector3 pos, Vector3 vel);
	ParticleGenerator(std::string name, double generation_prob, Vector3 pos, Vector3 vel);
	virtual ~ParticleGenerator();

	// Sets the particle to follow as the model
	void setParticle(Actor* model) noexcept;
	// Returns a list of new generated particles
	virtual std::list<Actor*> generateParticles() = 0;

	void initializeForces(ParticleForceRegistry* pf_registry) noexcept;
	bool forcesInitialized() const noexcept;
	void addForce(ForceGenerator* force);

	std::string getName() const;

	void moveLimitsTo(Vector3 const& pos);
protected:
	void applyForces(Actor* p);
	Actor* createParticle(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time);

	std::string _name;

	Actor* _model;
	Vector3 _mean_pos, _mean_vel;

	// Maximum number of particles to generate in a call to generateParticles()
	int _max_iteration_particles;
	
	// Probability to generate a particle
	double _generation_probability;
	std::uniform_real_distribution<> _random_probability;

	BoundingBox _limits;
	
	ParticleForceRegistry* _pf_registry;
	std::vector<ForceGenerator*> _force_generators;
};

