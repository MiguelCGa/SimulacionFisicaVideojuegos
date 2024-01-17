#pragma once

#include "../core.hpp"
#include "../Player.h"

class Obstacle {
public:
	Obstacle(Player* player, Vector3 const& pos);
	virtual void setPosition(Vector3 const&) = 0;
	virtual Vector3 getPosition() = 0;
	virtual void update(double t);
	virtual bool isAlive() { return true; }
protected:
	Vector3 spawnPos;
	BoundingBox posLimits;
	Player* _player;
};