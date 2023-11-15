#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() {
	
	ParticleGenerator* gen;

	// Uniform Particle Generator:

	/*gen = new UniformParticleGenerator("Gen1", Vector3(0, 0, 0), Vector3(0, 50, 0), 0.1, Vector3(3, 3, 3), Vector3(25, 1, 25));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);*/


	// Gaussian Particle Generator:


	gen = new GaussianParticleGenerator("Gen2", 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(10, 1, 10), Vector3(1, 1, 1));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);

	_force_generators.push_back(new GravityForceGenerator(Vector3(0, 0, 0)));
	gen->addForce(_force_generators.back());
	_force_generators.push_back(new WhirlwindForceGenerator(10.0f, 100.0f, 0.0f, BoundingBox(Vector3(0), 5000.0f)));
	gen->addForce(_force_generators.back());
	gen->initializeForces(&_particle_force_registry);


	/*_force_generators.push_back(new GravityForceGenerator(Vector3(0, 9.8, 0)));

	gen = new GaussianParticleGenerator("Gen3", 1, Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(100, 1, 1), Vector3(1, 1, 1));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);

	gen->addForce(_force_generators.back());
	gen->initializeForces(&_particle_force_registry);*/

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
