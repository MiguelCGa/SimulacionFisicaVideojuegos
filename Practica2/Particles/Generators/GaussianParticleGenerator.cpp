#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(std::string name, Vector3 pos, Vector3 vel, double generation_prob, Vector3 dev_pos, Vector3 dev_vel) :
	ParticleGenerator(name, pos, vel, generation_prob),
	std_dev_pos(dev_pos),
	std_dev_vel(dev_vel),
	std_dev_t(1.0),
	_pos_distribution(pos, dev_pos),
	_vel_distribution(vel, dev_vel)	{
}

std::list<Particle*>& GaussianParticleGenerator::generateParticles() {
	std::list<Particle*> particles;
	if (_random_probability(gen) < _generation_probability)
		particles.push_back(_model->clone(_pos_distribution(gen), _vel_distribution(gen)));
	return particles;
}