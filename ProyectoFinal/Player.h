#pragma once

#include "RigidBody.h"
#include "Forces/ParticleForceRegistry.h"
#include "Forces/Generators/JumpForceGenerator.h"
class Scene;

class Player : public RigidBody {
public:
	Player(Scene* scene, ParticleForceRegistry* pfRegistry, Vector3 init_pos);

	// Method to call when you kill the particle
	//virtual void kill();

	void keyPress(unsigned char key) override;
	void keyRelease(unsigned char key) override;
	// Updates the particle. Returns whether the particle is alive
	virtual bool integrate(double t);

	void restoreColor(double t);



protected:
	void handleJump(double t);
	void jump();
	void limitSpeed();
	void limitPosition();

	double speedLimit;

	bool jumped;
	bool jumping;
	const double jumpCoolDown;
	double jumpTime;
	ParticleForceRegistry* pfReg;
	Scene* _scene;
	physx::PxRigidBody* rb;
};