#pragma once

#include "../Particles/Particle.h"

class ForceGenerator {
public:
	ForceGenerator(double duration);
	virtual ~ForceGenerator() {}

	// Updates the force on the particle. Returns weather the force ended
	virtual bool updateForce(Particle* particle) = 0;
	bool updateTime(double t);
	bool isAlive() const noexcept;

	inline bool toggleActive() { return _active = !_active; }
protected:
	double _duration, _t;

	bool _active;
};

