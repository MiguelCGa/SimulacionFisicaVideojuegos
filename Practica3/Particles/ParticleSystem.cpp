#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() {
	
	ParticleGenerator* gen;

	// Uniform Particle Generator:

	/*gen = new UniformParticleGenerator("Gen1", Vector3(0, 0, 0), Vector3(0, 50, 0), 0.1, Vector3(3, 3, 3), Vector3(25, 1, 25));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);*/


	// Gaussian Particle Generator:

	gen = new GaussianParticleGenerator("Gen2", 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(100, 1, 1), Vector3(1, 1, 1));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);

	// Uniform Firework Generator:

	//gen = new UniformParticleGenerator("Gen1", Vector3(0, 0, 0), Vector3(0, 50, 0), 0.1, Vector3(3, 3, 3), Vector3(25, 1, 25));
	//gen->setParticle(new Firework(_particles, Vector3(50, -80, 0), 10.0f, Vector3(0, 40, 0), Vector4(255, 0, 0, 1), values::gravity, values::damping, 3.0));
	//_particle_generators.push_back(gen);

	// Gaussian Firework Generator:

	//gen = new GaussianParticleGenerator("Gen2", 0.05, Vector3(0, 0, 0), Vector3(0, 0, 25), Vector3(100, 1, 1), Vector3(1, 1, 1));
	//gen->setParticle(new Firework(_particles, Vector3(50, -80, 0), 10.0f, Vector3(0, 70, 0), Vector4(255, 0, 0, 1), values::gravity, values::damping, 3.0));
	//_particle_generators.push_back(gen);

}

ParticleSystem::~ParticleSystem() {
	for (Particle*& part : _particles) {
		delete part; 
		part = nullptr;
	}
	for (ParticleGenerator*& gen : _particle_generators) {
		delete gen; 
		gen = nullptr;
	}
}

void ParticleSystem::integrate(double t) {
	// Particle generation
	for (auto const& gen : _particle_generators) {
		_particles.splice(_particles.end(), gen->generateParticles());
	}

	// Force update
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

	// Particle update
	for (auto part_it = _particles.begin(); part_it != _particles.end(); ) {
		if ((*part_it)->integrate(t)) {
			++part_it;
		}
		else {
			(*part_it)->kill();
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _particles.erase(part_it);
		}
	}
}
