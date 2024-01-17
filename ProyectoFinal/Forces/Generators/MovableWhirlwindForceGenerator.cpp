#include "MovableWhirlwindForceGenerator.h"

MovableWhirlwindForceGenerator::MovableWhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area) :
	WhirlwindForceGenerator(K, height, k1, k2, area) {
}

MovableWhirlwindForceGenerator::MovableWhirlwindForceGenerator(const float K, const float height, const float k1, const float k2, BoundingBox const& area, double duration) :
	WhirlwindForceGenerator(K, height, k1, k2, area, duration) {
}

void MovableWhirlwindForceGenerator::setPosition(Vector3 const& pos) {
	_area.moveOriginTo(pos);
}
