#pragma once

#include <list>

#include "../Particle.h"
#include "../Generators/ParticleGenerator.h"
#include "../../Random/NormalDistributionVector3.h"

class Firework : public Particle {
public:
	Firework(std::list<Particle*>& childsList, Vector3 Pos, float Mass, Vector3 Vel = Vector3(0, 0, 0), Vector4 Color = genColors[Gen1], Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time);
	
	std::list<Particle*> explode();
	void kill() override;

protected:
	Firework* createChild();

	int numChilds;
	enum FireworkGeneration { Gen1, Gen2, LastGen };
	FireworkGeneration _myGen;
	std::list<Particle*>& _childsList;

	NormalDistributionVector3 _vel_distribution;

	static std::vector<Vector4> genColors;
};

