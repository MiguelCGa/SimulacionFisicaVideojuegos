#include "AnchoredSpringForceGenerator.h"
#include "../../Particles/Particle.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint, bool showAnchor) :
	ForceGenerator(),
	_k(k),
	_resting_length(resting_length),
	_anchorPoint(anchorPoint),
	item((showAnchor) ? new RenderItem(CreateShape(physx::PxBoxGeometry(1, 1, 1)), &_anchorPoint, Vector4(0, 0, 0, 1)) : nullptr) {
}
AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint) :
	AnchoredSpringForceGenerator(k, resting_length, anchorPoint, true) {
}

AnchoredSpringForceGenerator::~AnchoredSpringForceGenerator() {
	if (item != nullptr) delete item;
}

void AnchoredSpringForceGenerator::applyForce(Particle* p) {

	Vector3 relative_pos_vector = _anchorPoint.p - p->getPosition();

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	Vector3 force = relative_pos_vector * delta_x * _k;

	p->addForce(force);
}
