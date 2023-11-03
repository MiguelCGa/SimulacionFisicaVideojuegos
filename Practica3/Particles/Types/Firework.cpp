#include "Firework.h"

std::vector<Firework> Firework::fireworkPool = {

};

std::vector<Vector4> Firework::genColors = {
	Vector4(255, 0 , 0, 1),
	Vector4(0, 255 , 0, 1),
	Vector4(0, 0 , 255, 1)
};

Firework::Firework(std::list<Particle*>& childsList, Vector3 Pos, float Mass, Vector3 Vel, Vector4 Color, Vector3 gravity, float damping, double life_time) :
	Particle(Pos, Mass, Vel, Color, gravity, damping, life_time),
	_childsList(childsList),
	numChilds(10),
	_myGen(FireworkGeneration::Gen1),
	_vel_distribution(Vector3(0.0f, 25.0f, 0.0f), Vector3(10.0f, 1.0f, 10.0f)) {
}

std::list<Particle*> Firework::explode() {
	std::list<Particle*> nextGen;
	if (_myGen < LastGen) {
		for (int i = 0; i < numChilds; ++i) {
			nextGen.push_back(createChild());
		}
	}
	return nextGen;
}

void Firework::kill() {
	_childsList.splice(_childsList.end(), explode());
}

Particle* Firework::clone() const {
	return new Firework(_childsList, pose.p, _mass, _vel, renderItem->color, _gravity, _damping, _initial_life_time);
}

Firework* Firework::createChild() {
	Firework* newGen = static_cast<Firework*>(clone());
	newGen->initialize_as_child(_vel_distribution(gen()), static_cast<FireworkGeneration>(_myGen + 1), _initial_life_time);
	return newGen;
}

void Firework::initialize_as_child(Vector3 vel_offset, FireworkGeneration gen, double life_time) {
	_vel += vel_offset;
	_myGen = gen;
	renderItem->color = genColors[_myGen];
	_initial_life_time = life_time;
	_life_time = randomize_life_time(life_time);
}