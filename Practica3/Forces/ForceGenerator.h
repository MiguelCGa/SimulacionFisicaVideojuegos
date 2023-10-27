#pragma once

#include "../Particles/Particle.h"

class ForceGenerator {
public:
	ForceGenerator();

	// Updates the particle. Returns whether the particle is alive
	virtual void updateForce(Particle* particle, double t) = 0;
	bool updateTime(double t);
protected:
	double _t;
	double _duration;
};

