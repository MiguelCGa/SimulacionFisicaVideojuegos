#pragma once

#include <list>

#include "../Particle.h"
#include "../Generators/ParticleGenerator.h"
#include "../../Random/NormalDistributionVector3.h"

class Firework : public Particle {
public:
	Firework(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = Vector4(255, 255, 255, 1), Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time);
	
	std::list<Particle*> explode();
protected:
	Firework* createChild();

	int numChilds;
	enum FireworkGeneration { Gen1, Gen2, LastGen };
	FireworkGeneration _myGen;

	NormalDistributionVector3 _vel_distribution;
};

