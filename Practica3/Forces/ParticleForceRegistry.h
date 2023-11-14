#pragma once
#include "ForceGenerator.h"
#include <map>
#include <unordered_map>

class ParticleForceRegistry {
private:
	typedef std::multimap<ForceGenerator*, Particle*> FPmmap;
	typedef std::unordered_multimap<Particle*, FPmmap::iterator> PItummap;

	// Main registry
	FPmmap force_particle_registry;
	// Auxiliar registries for a better complexity in execution time
	PItummap p_fpregIt_registry;
	std::unordered_map<FPmmap::iterator, PItummap::iterator> fpregIt_pitregIt_registry;
	
public:
	// Complexity O(F*P)
	// Updates forces lifetime and aplies them to particles
	void updateForces(double t);

	// Complexity O(log(F*P))
	// Adds a registry with a particle and an aplied force
	void addRegistry(ForceGenerator* f, Particle* p);

	// Complexity O(F)
	// Deletes the particle registry and unlinks every force it has
	void deleteParticleRegistry(Particle* p);
};

