#include "Firework.h"

Firework::Firework(Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color, Vector3 gravity, float damping, double life_time) :
	Particle(Pos, Mass, Vel, Color, gravity, damping, life_time),
	numChilds(20),
	_myGen(FireworkGeneration::Gen1),
	_vel_distribution(Vector3(0.0f, 0.0f, 0.0f), Vector3(4.0f, 1.0f, 4.0f)) {
}

std::list<Particle*>& Firework::explode() {
	std::list<Particle*> nextGen;
	if (_myGen < LastGen) {
		for (int i = 0; i < numChilds; ++i) {
			nextGen.push_back(clone());
		}
	}
	return nextGen;
}

Firework* Firework::clone() {
	Firework* newGen = new Firework(pose.p, mass, _vel + _vel_distribution(random::gen), renderItem->color, _gravity, _damping, _initial_life_time);
	newGen->_myGen = static_cast<FireworkGeneration>(_myGen + 1);
	newGen->setOnDeath(_onDeath);
	return newGen;
}
