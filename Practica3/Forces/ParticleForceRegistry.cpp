#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double t) {
	ForceGenerator const* lastKey = nullptr;
	for (auto fpIt = force_particle_registry.begin(); fpIt != force_particle_registry.end();) {

		// Updates time for each different force
		if (fpIt->first != lastKey) { // has to be an ordered multimap so this works, otherwise this function would be cuadratic
			fpIt->first->updateTime(t);
			lastKey = fpIt->first;
		}

		// Update applied forces to particles 
		if (fpIt->first->updateForce(fpIt->second)) ++fpIt;

		else { // if the force ended remove the pair force particle from every registry
			auto e = fpregIt_pitregIt_registry.find(fpIt); // O(1)

			p_fpregIt_registry.erase(e->second); // remove from particle-iterator registry O(1)
			fpregIt_pitregIt_registry.erase(e); // remove from iterator-iterator registry O(1)
			fpIt = force_particle_registry.erase(fpIt); // remove from force-particle registry O(1)
		}
	}
}

void ParticleForceRegistry::addRegistry(ForceGenerator* f, Particle* p) {
	auto it = force_particle_registry.insert({ f, p }); // O(log(F*P))
	auto it2 = p_fpregIt_registry.insert({ p, it }); // O(1)
	fpregIt_pitregIt_registry.insert({ it, it2 }); // O(1)
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	auto range = p_fpregIt_registry.equal_range(p); // O(F)
	for (auto pitIt = range.first; pitIt != range.second; ) {
		fpregIt_pitregIt_registry.erase(pitIt->second); // O(1)(hashmap search)
		force_particle_registry.erase(pitIt->second); // O(1)

		pitIt = p_fpregIt_registry.erase(pitIt); // O(1)
	}
}
