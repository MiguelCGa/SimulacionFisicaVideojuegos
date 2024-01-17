#pragma once

#include "Obstacle.h"
#include "../Particles/ParticleSystem.h"
class Scene;
class Cannon : public Obstacle {
public:
	Cannon(Player* player, Vector3 const& pos, Scene* scene);
	virtual ~Cannon();
	virtual void setPosition(Vector3 const&);
	virtual Vector3 getPosition();
	virtual void update(double t);
protected:
	ParticleSystem* ps;
	RigidBody* base;
};