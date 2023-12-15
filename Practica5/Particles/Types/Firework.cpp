#include "Firework.h"
#include "../../Random/Utils.h"

std::vector<FireworkTemplate> Firework::fireworkPool = {
	{5.0f, Vector3(0.0f), Vector4(255, 0 , 0, 1), values::std_life_time, 10},
	{5.0f, Vector3(0.0f), Vector4(0, 255 , 0, 1), values::std_life_time, 5},
	{5.0f, Vector3(0.0f), Vector4(0, 0 , 255, 1), values::std_life_time, 0}
};

Firework::Firework(std::list<Actor*>& childsList, Vector3 Pos, FireworkGeneration gen, Vector3 gravity, float damping) :
	Particle(Pos, fireworkPool[gen].mass, fireworkPool[gen].init_vel, physx::PxGeometryType::eSPHERE, fireworkPool[gen].color, gravity, damping, fireworkPool[gen].life_time),
	_childsList(childsList),
	numChilds(fireworkPool[gen].num_childs),
	_myGen(gen),
	_vel_distribution(Vector3(10.0f), Vector3(10.0f)) {
}

std::list<Actor*> Firework::explode() {
	std::list<Actor*> nextGen;
	if (_myGen < LAST_GEN) {
		for (int i = 0; i < numChilds; ++i) {
			nextGen.push_back(createChild());
		}
	}
	return nextGen;
}

void Firework::kill() {
	_childsList.splice(_childsList.end(), explode());
}

Firework* Firework::clone() const {
	return new Firework(_childsList, pose.p, _myGen, _gravity, _damping);
}

Firework* Firework::createChild() {
	Firework* newGen = clone();
	newGen->initialize_as_child(_vel_distribution(gen()), _pos_limits);
	return newGen;
}

void Firework::initialize_as_child(Vector3 vel_offset, BoundingBox const& limits) {
	_myGen = static_cast<FireworkGeneration>(_myGen + 1);
	_mass = fireworkPool[_myGen].mass;
	_vel = fireworkPool[_myGen].init_vel;
	_renderItem->color = fireworkPool[_myGen].color;
	_initial_life_time = fireworkPool[_myGen].life_time;
	_life_time = fireworkPool[_myGen].life_time;
	numChilds = fireworkPool[_myGen].num_childs;


	_vel += vel_offset;
	_pos_limits = limits;
}