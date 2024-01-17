#pragma once

#include "RenderUtils.hpp"
#include "constants.h"
#include "Utils/BoundingBox.h"

class Actor {
public:
	Actor(RenderItem* renderItem, double life_time = values::std_life_time, BoundingBox pos_limits = BoundingBox());

	virtual ~Actor();

	virtual void addForce(Vector3 const& newForce) = 0;
	// Returns an identicle actor
	virtual Actor* clone() const = 0;
	// Initializeed the actor with said arguments
	virtual void initialize(Vector3 pos_offset, Vector3 vel_offset, double life_time, BoundingBox const& limits) = 0;
	// Returns an identicle actor initialized with said arguments
	Actor* clone_initialized(Vector3 pos_offset, Vector3 vel_offset, double life_time = values::std_life_time, BoundingBox const& limits = BoundingBox()) const;

	// Method to call when you kill the particle
	virtual void kill();

	virtual Vector3 getPosition() const = 0;
	virtual Vector3 getVelocity() const = 0;
	virtual float getMass() const = 0;
	virtual float getHeight() const;
	virtual float getSection() const;
	virtual void setPosition(Vector3 const&) {}


	// Updates the particle. Returns whether the particle is alive
	virtual bool integrate(double t);
	virtual void keyPress(unsigned char key);
	virtual void keyRelease(unsigned char key);


	// Returns whether the life time left is above 0
	bool isAlive() const;

protected:
	// Render
	RenderItem* _renderItem;
	// Life time
	double _initial_life_time, _life_time;
	BoundingBox _pos_limits;
};

inline physx::PxShape* createRegularShape(physx::PxGeometryType::Enum pt, float size = 1.0f) {
	switch (pt) {
	case physx::PxGeometryType::eSPHERE:
		return CreateShape(physx::PxSphereGeometry(size));
	case physx::PxGeometryType::eBOX:
		return CreateShape(physx::PxBoxGeometry(size, size, size));
	}
}