#include "ParticleGenerator.h"
#include "constants.h"
#include <iostream>
#include "GaussianParticleGenerator.h"

GaussianParticleGenerator::GaussianParticleGenerator(std::string name, Vector3 mean_pos, Vector3 mean_vel, double generation_prob) :
	ParticleGenerator(name, mean_pos, mean_vel, generation_prob) {

}

std::list<Particle*> GaussianParticleGenerator::generateParticles() {
	return std::list<Particle*>();
}
