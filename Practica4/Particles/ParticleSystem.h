#pragma once

#include <list>
#include "Generators/UniformParticleGenerator.h"
#include "Generators/GaussianParticleGenerator.h"
#include "Types/Firework.h"
#include "../Forces/ParticleForceRegistry.h"
#include "../Forces/Generators/GravityForceGenerator.h"
#include "../Forces/Generators/DragForceGenerator.h"
#include "../Forces/Generators/WhirlwindForceGenerator.h"
#include "../Forces/Generators/ExplosionForceGenerator.h"
#include "../Forces/Generators/ElasticRubberForceGenerator.h"
#include "../Forces/Generators/BuoyancyForceGenerator.h"
#include "../Forces/Generators/LiquidForceGenerator.h"

class ParticleSystem {
public:
	ParticleSystem();
	virtual ~ParticleSystem();

	// Updates the system
	virtual void integrate(double t);

	void explosion();

protected:
	void generateParticles();
	void updateForces(double t);
	void updateParticles(double t);

	std::list<Particle*> _particles;
	std::list<ParticleGenerator*> _particle_generators;
	ParticleForceRegistry _particle_force_registry;
	std::list<ForceGenerator*> _force_generators;
};

