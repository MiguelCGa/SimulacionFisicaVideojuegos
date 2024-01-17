#include "PlayScene.h"

PlayScene::PlayScene(physx::PxPhysics* gPhysics, physx::PxScene* mScene) :
	Scene(gPhysics, mScene),
	player(new Player(this, _mForceSystem->getRegistry(), Vector3(0))),
	cam(GetCamera()),
	height(0.0f),
	score(0),
	started(false),
	gameOver(false),
	fw_model(nullptr),
	spawnCoolDown(1),
	spawnTime(0) {
	
	_mActors.push_back(player);

	ParticleSystem* rain = new ParticleSystem(gPhysics, mScene);
	_mParticleSystems.push_back(rain);
	rain_model = new Particle(player->getPosition() + Vector3(0, 50, 0),
		1, Vector3(0.0f), physx::PxGeometryType::eSPHERE, Vector4(0, 0.3, 1, 1));
	GaussianParticleGenerator* gpg = new GaussianParticleGenerator("Rain", 1, Vector3(0), Vector3(0), Vector3(25), Vector3(1));
	gpg->setParticle(rain_model);
	rain->addParticleGenerator(gpg);
	rain->initializeForces(_mForceSystem->getRegistry());


	BuoyancyForceGenerator* bfg = new BuoyancyForceGenerator(BoundingBox(Vector3(0, -25, 0), Vector3(250, 25, 250)), 10);
	_mForceSystem->addForce(bfg);
	_mForceSystem->getRegistry()->addRegistry(player, bfg);
	
	display_text = "Jump. Consiste en saltar";
	setTextPos(250, 250);
	setTextColor(0, 0, 0);
}

PlayScene::~PlayScene() {
	for (auto& obs : _obstacles) {
		delete obs; obs = nullptr;
	}
}


void PlayScene::simulate(float t) {
	handleGameOver();
	handleScore();
	cameraMovement(t);
	updateRain();
	spawnObstacles(t);
	updateObstacles(t);
	Scene::simulate(t);
}

void PlayScene::handleGameOver() {
	auto pos = player->getPosition();
	if (abs(pos.x) > 3 || abs(pos.z) > 3) {
		if (!gameOver) {
			setTextPos(250, 250);
			display_text = "Game Over. Score: " + std::to_string(score);
			startFireworks();
		}
		gameOver = true;
	}
	if (gameOver) {
		fw_model->setPosition(player->getPosition());
	}
}

void PlayScene::cameraMovement(float t) {
	Vector3 dest = player->getPosition() - Vector3(-10, 0, -10);
	cam->setEye(cam->getEye() + (dest - cam->getEye()) * 8 * t);
	cam->setDir(player->getPosition() - cam->getEye());
}

void PlayScene::updateRain() {
	Vector3 offset(0);
	if (player->getVelocity().y < 0) offset.y = -50;
	else if (player->getVelocity().y > 0) offset.y = 50;
	rain_model->setPosition(player->getPosition() + offset);
}

void PlayScene::updateObstacles(float t) {
	for (auto part_it = _obstacles.begin(); part_it != _obstacles.end(); ) {
		(*part_it)->update(t);
		if ((*part_it)->isAlive() || ((*part_it)->getPosition() - player->getPosition()).magnitude() > 500) {
			++part_it;
		}
		else {
			delete (*part_it);
			(*part_it) = nullptr;
			part_it = _obstacles.erase(part_it);
		}
	}
}

void PlayScene::handleScore() {
	if (started && !gameOver) {
		if (player->getPosition().y > height) height = player->getPosition().y;
		score = height / 10;
		auto speed = player->getVelocity().magnitude();
		display_text = "Score: " + std::to_string(score);
	}
}

void PlayScene::startFireworks() {
	auto* fw = new ParticleSystem(_gPhysics, _mScene);
	_mParticleSystems.push_back(fw);
	auto* gen = new UniformParticleGenerator("GOFireworks", 0.1, Vector3(0), Vector3(0), Vector3(0), Vector3(5));
	fw->addParticleGenerator(gen);
	fw_model = new Firework(fw->getParticles(), player->getPosition());
	gen->setParticle(fw_model);
}

void PlayScene::spawnObstacles(float t) {
	if (score >= 5) {
		if (spawnTime > spawnCoolDown) {
			spawnTime -= spawnCoolDown;

			float altura = player->getPosition().y + (rand() % 55) + 35;
			float reparto;
			Vector3 obstaclePosition;
			Obstacle* obs;
			switch (rand() % 3) {
			case 0:
				reparto = rand() % 100;
				obstaclePosition = Vector3(-reparto, altura, -100 + reparto);
				obs = new Tornado(player, obstaclePosition, this);
				break;
			case 1:
				reparto = rand() % 100;
				obstaclePosition = Vector3(-reparto, altura, -100 + reparto);
				obs = new Block(player, obstaclePosition, this);
				break;
			case 2:
				float reparto = rand() % 200;
				Vector3 obstaclePosition(-reparto, altura + 25, -200 + reparto);
				obs = new Cannon(player, obstaclePosition, this);
				break;
			}
			_obstacles.push_back(obs);
		}
		else spawnTime += t;
	}
}

void PlayScene::explosion() {
	const Vector3 origin(0);
	constexpr double duration = 2.0;
	constexpr float K = 500000.0f;
	ExplosionForceGenerator* e = new ExplosionForceGenerator(origin, duration, K);
	addForce(e);
}

void PlayScene::keyPress(unsigned char key, const physx::PxTransform& cam) {
	switch (key) {
	case 'J':
		if (!started) {
			started = true;
			setTextPos(0, 0);
		}
		break;
	}
	if (!gameOver) Scene::keyPress(key, cam);
}
