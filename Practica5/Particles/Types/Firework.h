#pragma once

#include <list>

#include "../Particle.h"
#include "../Generators/ParticleGenerator.h"
#include "../../Random/NormalDistributionVector3.h"

struct FireworkTemplate {
	float mass;
	Vector3 init_vel;
	Vector4 color;
	double life_time;
	unsigned int num_childs;
};
enum FireworkGeneration { GEN_1, GEN_2, LAST_GEN };

class Firework : public Particle {
public:
	Firework(std::list<Actor*>& childsList, Vector3 Pos, FireworkGeneration gen = GEN_1, Vector3 gravity = values::gravity, float damping = values::damping);
	// Returns a list with numChild particles of the next generation
	std::list<Actor*> explode();
	void kill() override;
	Firework* clone() const override;


protected:
	// Clones the firework an initializes it as its child
	Firework* createChild(); 
	// Initialize the firework with the parameters asked
	void initialize_as_child(Vector3 vel_offset, BoundingBox const& limits);

	int numChilds; // Number of childs to generate on death
	FireworkGeneration _myGen;
	std::list<Actor*>& _childsList; // List to attatch de childs to

	NormalDistributionVector3 _vel_distribution;

	static std::vector<Vector4> genColors;

	static std::vector<FireworkTemplate> fireworkPool;
};

