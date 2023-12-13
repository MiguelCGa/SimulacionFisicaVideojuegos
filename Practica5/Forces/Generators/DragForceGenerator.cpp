#include "DragForceGenerator.h"

DragForceGenerator::DragForceGenerator() : 
	DragForceGenerator(0.02, 0.1) {
}

DragForceGenerator::DragForceGenerator(const float k1, const float k2) :
	DragForceGenerator(k1, k2, BoundingBox()) {
}

DragForceGenerator::DragForceGenerator(const float k1, const float k2, BoundingBox const& area) :
	ForceGenerator(area),
	_k1(k1),
	_k2(k2) {

}

void DragForceGenerator::applyForce(Actor* p) {
	Vector3 v = p->getVelocity();
	float drag_coef = v.normalize();
	drag_coef = _k1 * drag_coef + _k2 * drag_coef * drag_coef;
	Vector3 dragF = -v * drag_coef;
	p->addForce(dragF);
}
