#pragma once

#include "Obstacle.h"
class Scene;
class Block : public Obstacle {
public:
	Block(Player* player, Vector3 const& pos, Scene* scene);
	virtual ~Block();
	virtual void setPosition(Vector3 const&);
	virtual Vector3 getPosition();
	virtual void update(double t);
protected:
	RigidBody* bloque;
	double speed;
	Vector3 direction;
};