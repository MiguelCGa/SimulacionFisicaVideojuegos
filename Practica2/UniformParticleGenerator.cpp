#include "ParticleGenerator.h"
#include "constants.h"
#include <iostream>
#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(std::string name, Vector3 mean_pos, Vector3 mean_vel, double generation_prob, Vector3 pos_width, Vector3 vel_width) :
	ParticleGenerator(name, mean_pos, mean_vel, generation_prob),
	_pos_distribution(mean_pos, pos_width), 
	_vel_distribution(mean_vel, vel_width) {

}

std::list<Particle*> UniformParticleGenerator::generateParticles() {
	std::list<Particle*> particles;
	if (((rand() % 100) / 100.0) < _generation_probability) 
		particles.push_back(_model->clone(_pos_distribution(gen), _vel_distribution(gen)));
	return particles;
}
