#pragma once

#include <list>
#include "../Forces/ParticleForceRegistry.h"

class ForceSystem {
public:
	ForceSystem();
	virtual ~ForceSystem();


	ForceGenerator* addForce(ForceGenerator* fg);

	ParticleForceRegistry* getRegistry();

	// Updates the system
	virtual void integrate(double t);
protected:

	void updateForces(double t);

	ParticleForceRegistry _particle_force_registry;
	std::list<ForceGenerator*> _force_generators;
};

