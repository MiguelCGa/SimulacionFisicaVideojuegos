#include "UniformParticleGenerator.h"

UniformParticleGenerator::UniformParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 pos_width, Vector3 vel_width) :
	ParticleGenerator(name, generation_prob, pos, vel),
	_pos_distribution(pos, pos_width), 
	_vel_distribution(vel, vel_width) {

}

std::list<Particle*> UniformParticleGenerator::generateParticles() {
	std::list<Particle*> particles;
	for (int i = 0; i < _max_iteration_particles; ++i)
		if (_random_probability(gen()) < _generation_probability)
			particles.push_back(createParticle(_pos_distribution(gen()), _vel_distribution(gen())));
	return particles;
}