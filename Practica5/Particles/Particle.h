#pragma once

#include "../RenderUtils.hpp"
#include "../constants.h"
#include "../Utils/BoundingBox.h"
#include "../Actor.h"

class Particle : public Actor {
public:
	Particle(Vector3 pos, float mass, Vector3 vel = Vector3(0.0f), physx::PxGeometryType::Enum form = physx::PxGeometryType::eSPHERE, Vector4 color = Vector4(255, 255, 255, 1), Vector3 gravity = values::gravity, float damping = values::damping, double life_time = values::std_life_time, BoundingBox const& pos_limits = BoundingBox());

	// Updates the particle. Returns whether the particle is alive
	bool integrate(double t) override;

	float getMass() const noexcept override;
	Vector3 getPosition() const override;
	Vector3 getVelocity() const override;

	void addForce(Vector3 const& newForce) override;
	void clearForce();

	// Returns an identicle particle
	Particle* clone() const override;
	// Initializeed the particle with said arguments
	void initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time, BoundingBox const& limits = BoundingBox()) override;

protected:

	// Mass
	float _mass, _inverse_mass;
	// Movement
	physx::PxTransform pose;
	Vector3 _vel, _accel, _gravity;
	float _damping;
	// Accumulated forces
	Vector3 _force;
};