#pragma once

#include "Obstacle.h"
#include "../Particles/ParticleSystem.h"
#include "../Forces/Generators/MovableWhirlwindForceGenerator.h"
class Scene;
class Tornado : public Obstacle {
public:
	Tornado(Player* player, Vector3 const& pos, Scene* scene);
	virtual ~Tornado();
	void setPosition(Vector3 const& pos) override;
	Vector3 getPosition() override;
	void update(double t) override;
	void move(Vector3 const& offset);
private:
	MovableWhirlwindForceGenerator* forceGen;
	ParticleSystem* particles;
	BoundingBox effectArea;
	Particle* torn_core;
	Scene* myScene;
	ParticleGenerator* gen;
	double speed;
	Vector3 moveDir;
};