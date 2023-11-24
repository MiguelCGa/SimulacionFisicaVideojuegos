#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() {
	
	
	Particle* p = new Particle(Vector3(1, 0, 0), 1);
	_particles.push_back(p);

	AnchoredSpringForceGenerator* s = new AnchoredSpringForceGenerator(1.0, 10.0, Vector3(0));
	//GravityForceGenerator* g = new GravityForceGenerator(Vector3(0, -9.8, 0));

	_force_generators.push_back(s);
	//_force_generators.push_back(g);

	_particle_force_registry.addRegistry(p, s);
	//_particle_force_registry.addRegistry(p, g);
}

ParticleSystem::~ParticleSystem() {
	for (Particle*& part : _particles) {
		delete part; 
		part = nullptr;
	}
	for (ParticleGenerator*& generator : _particle_generators) {
		delete generator;
		generator = nullptr;
	}
	for (ForceGenerator*& force : _force_generators) {
		delete force; 
		force = nullptr;
	}
	
}

void ParticleSystem::integrate(double t) {
	generateParticles();
	updateForces(t);
	updateParticles(t);
}

void ParticleSystem::explosion() {
	auto f = new ExplosionForceGenerator(Vector3(0), 2.0, 500.0f);
	_force_generators.push_back(f);
	for (auto& p : _particles) {
		_particle_force_registry.addRegistry(p, f);
	}
	for (auto& pg : _particle_generators) {
		if (pg->forcesInitialized()) pg->addForce(f);
	}
}

void ParticleSystem::generateParticles() {
	for (auto const& gen : _particle_generators) {
		_particles.splice(_particles.end(), gen->generateParticles());
	}
}

void ParticleSystem::updateForces(double t) {
	_particle_force_registry.updateForces(t);
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

void ParticleSystem::updateParticles(double t) {
	for (auto part_it = _particles.begin(); part_it != _particles.end(); ) {
		if ((*part_it)->integrate(t)) {
			++part_it;
		}
		else {
			_particle_force_registry.deleteParticleRegistry(*part_it);
			(*part_it)->kill();
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _particles.erase(part_it);
		}
	}
}
