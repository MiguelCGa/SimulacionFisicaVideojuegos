#pragma once
#include "../Scene.h"
#include "../Player.h"
#include "../Obstacles/Tornado.h"
#include "../Obstacles/Block.h"
#include "../Obstacles/Cannon.h"

class PlayScene : public Scene {
public:
	PlayScene(physx::PxPhysics* gPhysics, physx::PxScene* mScene);
	virtual ~PlayScene();
	void simulate(float t) override;

	void handleGameOver();
	void cameraMovement(float t);
	void updateRain();
	void updateObstacles(float t);
	void handleScore();
	void startFireworks();
	void spawnObstacles(float t);

	void explosion();

	void keyPress(unsigned char key, const physx::PxTransform& cam) override;
protected:
	Camera* cam;

	Player* player;

	Particle* rain_model;
	std::list<Obstacle*> _obstacles;

	float height;
	int score;
	bool started, gameOver;
	Firework* fw_model;

	float spawnCoolDown, spawnTime;
};

