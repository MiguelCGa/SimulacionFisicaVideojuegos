#pragma once

#include "../Particles/Particle.h"

class ForceGenerator {
public:
	ForceGenerator();

	// Updates the force on the particle. Returns weather the force ended
	virtual bool updateForce(Particle* particle) = 0;
	bool updateTime(double t);
	bool isAlive() const;
protected:
	double _t;
	double _duration;
};

