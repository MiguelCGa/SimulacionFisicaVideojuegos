#include "LiquidForceGenerator.h"

LiquidForceGenerator::LiquidForceGenerator(BoundingBox area, float d, float k1, float k2) : 
	ForceGenerator(-1.0),
	BuoyancyForceGenerator(area, d),
	DragForceGenerator(k1, k2, area) {
}

bool LiquidForceGenerator::updateForce(Particle* p) {
	return BuoyancyForceGenerator::updateForce(p) && DragForceGenerator::updateForce(p);
}
