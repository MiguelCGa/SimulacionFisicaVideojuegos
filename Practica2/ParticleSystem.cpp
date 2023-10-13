#include "ParticleSystem.h"
#include "constants.h"
#include <iostream>

ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::integrate(double t) {

	for (auto const& gen : _particle_generators) {
		_particles.splice(_particles.end(), gen->generateParticles());
	}

	for (auto it = _particles.begin(); it != _particles.end(); ) {
		if ((*it)->isAlive()) {
			(*it)->integrate(t);
			++it;
		}
		else {
			it = _particles.erase(it);
		}
	}
}