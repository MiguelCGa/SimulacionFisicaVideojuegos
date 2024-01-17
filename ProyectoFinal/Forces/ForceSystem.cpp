#include "ForceSystem.h"

ForceSystem::ForceSystem() {
							
}

ForceSystem::~ForceSystem() {
	for (ForceGenerator*& force : _force_generators) {
		delete force; 
		force = nullptr;
	}
}


ForceGenerator* ForceSystem::addForce(ForceGenerator* fg) {
	_force_generators.push_back(fg);
	return fg;
}

ParticleForceRegistry* ForceSystem::getRegistry() {
	return &_particle_force_registry;
}

void ForceSystem::integrate(double t) {
	_particle_force_registry.updateForces(t);
	updateForces(t);
}

void ForceSystem::updateForces(double t) {
	for (auto force_it = _force_generators.begin(); force_it != _force_generators.end(); ) {
		// Non-alive forces get erased on the next iteration so registry works well
		if (!(*force_it)->isAlive()) {
			delete (*force_it);
			(*force_it) = nullptr;
			force_it = _force_generators.erase(force_it);
		}
		else {
			(*force_it)->updateTime(t);
			++force_it;
		}
	}
}
