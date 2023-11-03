#pragma once

#include <list>

#include "../Particle.h"
#include "../Generators/ParticleGenerator.h"
#include "../../Random/NormalDistributionVector3.h"

class Firework : public Particle {
	enum FireworkGeneration { Gen1, Gen2, LastGen };
public:
	Firework(std::list<Particle*>& childsList, Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = genColors[Gen1], Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time);
	// Returns a list with numChild particles of the next generation
	std::list<Particle*> explode();
	void kill() override;
	Particle* clone() const override;


protected:
	// Clones the firework an initializes it as its child
	Firework* createChild(); 
	// Initialize the firework with the parameters asked
	void initialize_as_child(Vector3 vel_offset, FireworkGeneration gen, double life_time);

	int numChilds; // Number of childs to generate on death
	FireworkGeneration _myGen;
	std::list<Particle*>& _childsList; // List to attatch de childs to

	NormalDistributionVector3 _vel_distribution;

	static std::vector<Vector4> genColors;

	static std::vector<Firework> fireworkPool;
};

