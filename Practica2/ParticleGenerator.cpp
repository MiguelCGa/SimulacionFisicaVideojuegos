#include "ParticleGenerator.h"
#include "constants.h"
#include <iostream>

ParticleGenerator::ParticleGenerator(std::string name, Vector3 mean_pos, Vector3 mean_vel, double generation_prob) : 
	_name(name), 
	_mean_pos(mean_pos),
	_mean_vel(mean_vel), 
	_generation_probability(generation_prob),
	_num_particles(0),
	_model(nullptr) {

}

ParticleGenerator::~ParticleGenerator() {

}

void ParticleGenerator::setParticle(Particle* model) {
	_model = model;
}