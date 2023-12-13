#pragma once
#include "ForceGenerator.h"
#include <unordered_map>

class ParticleForceRegistry : 
	private std::unordered_multimap<Actor*, ForceGenerator*> {

public:
	// Aplies forces to particles
	void updateForces(double t);

	// Adds a registry with a particle and an aplied force
	void addRegistry(Actor* p, ForceGenerator* f);

	// Deletes the particle registry and unlinks every force it has
	void deleteParticleRegistry(Actor* p); 

};

