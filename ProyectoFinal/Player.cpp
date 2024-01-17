#include "Player.h"
#include "Scene.h"
#include <iostream>

Player::Player(Scene* scene, ParticleForceRegistry* pfRegistry, Vector3 init_pos) :
	RigidBody(scene->getPxPhysics(), scene->getPxScene(),
		init_pos, 
		physx::PxActorType::eRIGID_DYNAMIC, 
		createRegularShape(physx::PxGeometryType::eBOX), 1,
		Vector4(1),
		-1, 
		BoundingBox()),
	_scene(scene),
	jumped(false),
	jumping(false),
	pfReg(pfRegistry),
	jumpCoolDown(0.1), 
	jumpTime(0.1),
	speedLimit(25),
	rb(getRigidBody()){
	//rb->setLinearVelocity(Vector3(5, 0, 0));
}

void Player::keyPress(unsigned char key) {
	switch (key) {
	case 'J':
		jumping = true;
		break;
	default:
		break;
	}
}

void Player::keyRelease(unsigned char key) {
	switch (key) {
	case 'J':
		jumping = false;
		break;
	default:
		break;
	}
}

bool Player::integrate(double t) {

	restoreColor(t);

	handleJump(t);

	limitSpeed();


	return isAlive();
}

void Player::restoreColor(double t) {
	if (_renderItem->color.z < 1) {
		_renderItem->color = _renderItem->color + Vector4(1, 0, 1, 0) * t;
	}
	else _renderItem->color = Vector4(1);
}

void Player::handleJump(double t) {
	if (jumpTime >= jumpCoolDown) {
		if (jumping && !jumped) {
			jump();
			jumpTime -= jumpCoolDown;
		}
	}
	else jumpTime += t;
	jumped = jumping;
}

void Player::jump() {
	pfReg->addRegistry(this, _scene->addForce(new JumpForceGenerator(10000, rb->getInvMass(), getVelocity().magnitude())));
	_renderItem->color = Vector4(0, 1, 0, 1);
}

void Player::limitSpeed() {
	Vector3 vel = getVelocity();
	if (vel.y > 0) {
		if (getVelocity().magnitudeSquared() > speedLimit * speedLimit) {
			rb->setLinearVelocity(rb->getLinearVelocity().getNormalized() * speedLimit);
		}
	}
	else {
		if (getVelocity().magnitudeSquared() > speedLimit * speedLimit * 4) {
			rb->setLinearVelocity(rb->getLinearVelocity().getNormalized() * speedLimit * 2);
		}
	}

	rb->setAngularVelocity(Vector3(0));
}

void Player::limitPosition() {
	auto vel = getVelocity();
	if (getPosition().y < 0 && vel.y < 0) {
		vel.y = 0;
		rb->setLinearVelocity(vel);
	}
}
