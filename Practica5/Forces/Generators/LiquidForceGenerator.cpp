#include "LiquidForceGenerator.h"

LiquidForceGenerator::LiquidForceGenerator(BoundingBox const& area, float d, float k1, float k2) : 
	ForceGenerator(area),
	BuoyancyForceGenerator(area, d),
	DragForceGenerator(k1, k2, area) {
}

void LiquidForceGenerator::applyForce(Particle* p) {
	BuoyancyForceGenerator::applyForce(p);
	DragForceGenerator::applyForce(p);
}
