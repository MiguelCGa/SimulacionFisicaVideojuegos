#include "ParticleForceRegistry.h"

void ParticleForceRegistry::updateForces(double t) {
	for (auto it = begin(); it != end();) {
		if (it->second->updateForce(it->first)) ++it;
		else it = erase(it);
	}
}

void ParticleForceRegistry::addRegistry(Particle* p, ForceGenerator* f) {
	insert({ p, f });
}

void ParticleForceRegistry::deleteParticleRegistry(Particle* p) {
	erase(p);
}