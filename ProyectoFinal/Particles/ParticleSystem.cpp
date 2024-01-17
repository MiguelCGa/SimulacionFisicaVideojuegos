#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(physx::PxPhysics* gPhysics, physx::PxScene* mScene) : 
	_maxElems(500),
	_particle_force_registry(nullptr) {		
}

ParticleSystem::~ParticleSystem() {
	for (Actor*& part : _particles) {
		delete part; 
		part = nullptr;
	}
	for (ParticleGenerator*& generator : _particle_generators) {
		delete generator;
		generator = nullptr;
	}
	
}

void ParticleSystem::integrate(double t) {
	generateParticles();
	updateParticles(t);
}

ParticleGenerator* ParticleSystem::addParticleGenerator(ParticleGenerator* pg) {
	_particle_generators.push_back(pg);
	_name_pg.insert({pg->getName(), pg});
	return pg;
}

ParticleGenerator* ParticleSystem::getParticleGenerator(std::string name) {
	return _name_pg.at(name);
}

void ParticleSystem::initializeForces(ParticleForceRegistry* pfRegistry) noexcept {
	_particle_force_registry = pfRegistry;
}

void ParticleSystem::addForce(ForceGenerator* fg) {
	if (_particle_force_registry == nullptr) return;

	for (auto& p : _particles) {
		_particle_force_registry->addRegistry(p, fg);
	}
	for (auto& pg : _particle_generators) {
		if (pg->forcesInitialized()) pg->addForce(fg);
	}
}

std::list<Actor*>& ParticleSystem::getParticles() {
	return _particles;
}

void ParticleSystem::generateParticles() {
	for (auto const& gen : _particle_generators) {
		if (_particles.size() <= _maxElems) 
			_particles.splice(_particles.end(), gen->generateParticles());
	}
}

void ParticleSystem::updateParticles(double t) {
	for (auto part_it = _particles.begin(); part_it != _particles.end(); ) {
		if ((*part_it)->integrate(t)) {
			++part_it;
		}
		else {
			if (_particle_force_registry != nullptr) _particle_force_registry->deleteParticleRegistry(*part_it);
			(*part_it)->kill();
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _particles.erase(part_it);
		}
	}
}
