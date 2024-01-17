#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(std::string name, double generation_prob, BoundingBox limits, Vector3 mean_pos, Vector3 mean_vel) :
	_name(name),
	_generation_probability(generation_prob),
	_limits(limits),
	_mean_pos(mean_pos),
	_mean_vel(mean_vel), 
	_max_iteration_particles(3),
	_model(nullptr),
	_random_probability(0.0, 1.0),
	_pf_registry(nullptr) {
}
ParticleGenerator::ParticleGenerator(std::string name, double generation_prob, Vector3 mean_pos, Vector3 mean_vel) :
	ParticleGenerator(name, generation_prob, BoundingBox(), mean_pos, mean_vel) {
}

ParticleGenerator::~ParticleGenerator() {
	delete _model; _model = nullptr;
}

void ParticleGenerator::setParticle(Actor* model) noexcept {
	_model = model;
}

void ParticleGenerator::initializeForces(ParticleForceRegistry* pf_registry) noexcept {
	_pf_registry = pf_registry;
}

bool ParticleGenerator::forcesInitialized() const noexcept {
	return _pf_registry != nullptr;
}

void ParticleGenerator::addForce(ForceGenerator* force) {
	_force_generators.push_back(force);
}

std::string ParticleGenerator::getName() const {
	return _name;
}

void ParticleGenerator::moveLimitsTo(Vector3 const& pos) {
	_limits.moveOriginTo(pos);
}

void ParticleGenerator::applyForces(Actor* p) {
	if (!forcesInitialized() && _force_generators.size() > 0)
		throw std::exception("Cannot apply forces without initializing.");

	for (auto force_it = _force_generators.begin(); force_it != _force_generators.end();) {
		if ((*force_it)->isAlive()) {
			_pf_registry->addRegistry(p, *force_it);
			++force_it;
		}
		else force_it = _force_generators.erase(force_it);
	}
}

Actor* ParticleGenerator::createParticle(Vector3 pos_offset, Vector3 vel_offset, double life_time) {
	Actor* p = _model->clone_initialized(pos_offset, vel_offset, life_time, _limits);
	applyForces(p);
	return p;
}
