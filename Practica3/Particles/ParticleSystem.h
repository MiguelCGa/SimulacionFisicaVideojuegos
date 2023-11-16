#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "Types/Firework.h"
#include "../Forces/ParticleForceRegistry.h"
#include "../Forces/Generators/GravityForceGenerator.h"
#include "../Forces/Generators/WhirlwindForceGenerator.h"
#include "../Forces/Generators/ExplosionForceGenerator.h"

class ParticleSystem {
public:
	enum class myForces : int { GRAVITY, NEG_GRAVITY, WIND, WHIRLWIND, lastForce };


	ParticleSystem();
	virtual ~ParticleSystem();

	// Updates the system
	virtual void integrate(double t);

	void explosion();

	inline void toggleForce(myForces mF) { _toggle_forces[(int)mF]->toggleActive(); }

protected:
	void generateParticles();
	void updateForces(double t);
	void updateParticles(double t);

	void addToggleForce(myForces mF);

	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;
	ParticleForceRegistry _particle_force_registry;
	std::list<ForceGenerator*> _force_generators;

	std::vector<ForceGenerator*> _toggle_forces;
};

