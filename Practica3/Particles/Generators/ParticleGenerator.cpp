#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(std::string name, double generation_prob, Vector3 mean_pos, Vector3 mean_vel) :
	_name(name), 
	_mean_pos(mean_pos),
	_mean_vel(mean_vel), 
	_generation_probability(generation_prob),
	_max_iteration_particles(3),
	_model(nullptr),
	_random_probability(0.0, 1.0),
	_pf_registry(nullptr) {
}

ParticleGenerator::~ParticleGenerator() {
	delete _model; _model = nullptr;
}

void ParticleGenerator::setParticle(Particle* model) noexcept {
	_model = model;
}

void ParticleGenerator::initializeForces(ParticleForceRegistry* pf_registry) noexcept {
	_pf_registry = pf_registry;
}

void ParticleGenerator::addForce(ForceGenerator* force) {
	_force_generators.push_back(force);
}

void ParticleGenerator::applyForces(Particle* p) {
	if (_pf_registry == nullptr && _force_generators.size() > 0) 
		throw std::exception("Cannot apply forces without initializing.");
	for (auto& force : _force_generators) {
		_pf_registry->addRegistry(p, force);
	}
}

Particle* ParticleGenerator::createParticle(Vector3 pos_offset, Vector3 vel_offset, double life_time) {
	Particle* p = _model->clone_initialized(pos_offset, vel_offset, life_time);
	applyForces(p);
	return p;
}
