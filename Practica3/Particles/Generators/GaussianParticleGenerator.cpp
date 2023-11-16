#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(std::string name, double generation_prob, BoundingBox limits, Vector3 mean_pos, Vector3 mean_vel, Vector3 dev_pos, Vector3 dev_vel) :
	ParticleGenerator(name, generation_prob, limits, mean_pos, mean_vel),
	std_dev_pos(dev_pos),
	std_dev_vel(dev_vel),
	std_dev_t(1.0),
	_pos_distribution(mean_pos, dev_pos),
	_vel_distribution(mean_vel, dev_vel),
	_life_time_distribution(values::std_life_time, std_dev_t) {
}
GaussianParticleGenerator::GaussianParticleGenerator(std::string name, double generation_prob, Vector3 mean_pos, Vector3 mean_vel, Vector3 dev_pos, Vector3 dev_vel) :
	GaussianParticleGenerator(name, generation_prob, BoundingBox(), mean_pos, mean_vel, dev_pos, dev_vel) {
}

std::list<Particle*> GaussianParticleGenerator::generateParticles() {
	std::list<Particle*> particles;
	for (int i = 0; i < _max_iteration_particles; ++i)
		if (_random_probability(gen()) < _generation_probability)
			particles.push_back(createParticle(_pos_distribution(gen()), _vel_distribution(gen()), _life_time_distribution(gen())));
		
	return particles;
}