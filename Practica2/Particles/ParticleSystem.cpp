#include "ParticleSystem.h"
#include <iostream>

ParticleSystem::ParticleSystem() {
	
	ParticleGenerator* gen;
	//gen = new UniformParticleGenerator("Gen1", Vector3(0, 0, 0), Vector3(0, 50, 0), 0.1, Vector3(3, 3, 3), Vector3(25, 1, 25));
	//gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	//_particle_generators.push_back(gen);
	
	gen = new GaussianParticleGenerator("Gen2", Vector3(0, 0, 0), Vector3(0, 0, 0), 0.1, Vector3(100, 1, 1), Vector3(1, 1, 1));
	gen->setParticle(new Particle(Vector3(0, 0, 0), 1));
	_particle_generators.push_back(gen);

	Firework* f = new Firework(Vector3(0, 30, 0), 10.0f, Vector3(0, 70, 0), Vector4(255, 0, 0, 1));
	f->setOnDeath([&](Particle* p) {
		_particles.splice(_particles.end(), static_cast<Firework*>(p)->explode());
	});
	_particles.push_back(f);
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
	for (auto const& gen : _particle_generators) {
		_particles.splice(_particles.end(), gen->generateParticles());
	}

	for (auto it = _particles.begin(); it != _particles.end(); ) {
		if ((*it)->integrate(t)) {
			++it;
		}
		else {
			(*it)->kill();
			delete (*it);
			(*it) = nullptr;
			it = _particles.erase(it);
		}
	}
}
