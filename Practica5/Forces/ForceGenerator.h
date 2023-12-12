#pragma once

#include "../Particles/Particle.h"

class ForceGenerator {
public:
	/// <summary>
	/// Creates an endless force applying in any position
	/// </summary>
	ForceGenerator();
	/// <summary>
	/// Creates a force with given duration applying in any position.
	/// </summary>
	/// <param name="duration: ">Seconds until the force stops.</param>
	ForceGenerator(double duration);
	/// <summary>
	/// Creates an endless force applying in the given area.
	/// </summary>
	/// <param name="area: ">BoundingBox within which the force is to be applied.</param>
	ForceGenerator(BoundingBox const& area);
	/// <summary>
	/// Creates a force with given duration applying in the given area.
	/// </summary>
	/// <param name="duration: ">Seconds until the force stops.</param>
	/// <param name="area: ">BoundingBox within which the force is to be applied.</param>
	ForceGenerator(double duration, BoundingBox const& area);

	virtual ~ForceGenerator() {}

	// Updates the force on the particle. Returns weather the force ended.
	bool updateForce(Particle* particle);
	bool updateTime(double t);
	/// <returns>
	/// Whether the force is alive.
	/// </returns>
	bool isAlive() const noexcept;
protected:
	// Applies the force on the particle.
	virtual void applyForce(Particle* particle) = 0;

	const BoundingBox _area;
	const double _duration;
	double _t;
};

