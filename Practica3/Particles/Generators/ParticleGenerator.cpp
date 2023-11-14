#include "ParticleGenerator.h"

ParticleGenerator::ParticleGenerator(std::string name, double generation_prob, Vector3 mean_pos, Vector3 mean_vel) :
	_name(name), 
	_mean_pos(mean_pos),
	_mean_vel(mean_vel), 
	_generation_probability(generation_prob),
	_max_iteration_particles(3),
	_model(nullptr),
	_random_probability(0.0, 1.0) {
}

ParticleGenerator::~ParticleGenerator() {
	delete _model; _model = nullptr;
}

void ParticleGenerator::setParticle(Particle* model) noexcept {
	_model = model;
}