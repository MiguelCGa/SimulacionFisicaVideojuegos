#pragma once

#include "../RenderUtils.hpp"
#include "../constants.h"
#include "../Utils/BoundingBox.h"

class Particle {
public:
	Particle(Vector3 Pos, float Mass, Vector3 Vel = Vector3(0.0f), Vector4 Color = Vector4(255, 255, 255, 1), Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time, BoundingBox pos_limits = BoundingBox());
	virtual ~Particle();

	// Updates the particle. Returns whether the particle is alive
	virtual bool integrate(double t);
	// Returns whether the life time left is above 0
	bool isAlive() const noexcept;

	float getMass() const noexcept;
	Vector3 getPosition() const;
	Vector3 getVelocity() const;

	void addForce(Vector3 const& newForce);
	void clearForce();

	// Returns an identicle particle
	virtual Particle* clone() const;
	// Initializeed the particle with said arguments
	void initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time, BoundingBox limits = BoundingBox());
	// Returns an identicle particle initialized with said arguments
	Particle* clone_initialized(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time, BoundingBox limits = BoundingBox()) const;

	// Method to call when you kill the particle
	virtual void kill();
	// Returns the life time passed randomized in a 20%
	double randomize_life_time(double life_time);

protected:
	// Mass
	float _mass, _inverse_mass;
	// Movement
	physx::PxTransform pose;
	Vector3 _vel, _accel, _gravity;
	float _damping;
	// Accumulated forces
	Vector3 _force;
	// Render
	RenderItem* renderItem;
	// Life time
	double _initial_life_time, _life_time;
	BoundingBox _pos_limits;
};

