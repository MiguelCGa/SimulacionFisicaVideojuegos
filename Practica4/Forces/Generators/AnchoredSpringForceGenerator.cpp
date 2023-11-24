#include "AnchoredSpringForceGenerator.h"
#include "../../Particles/Particle.h"

AnchoredSpringForceGenerator::AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint) :
	ForceGenerator(-1.0),
	_k(k),
	_resting_length(resting_length),
	_anchorPoint(anchorPoint),
	eeeeeeee(anchorPoint),
	item(new RenderItem(CreateShape(physx::PxBoxGeometry(1, 1, 1)), &eeeeeeee, Vector4(0, 0, 0, 1))){
;

}

bool AnchoredSpringForceGenerator::updateForce(Particle* p) {

	Vector3 relative_pos_vector = _anchorPoint - p->getPosition();

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - _resting_length;

	Vector3 force = relative_pos_vector * delta_x * _k;

	p->addForce(force);

	return isAlive();
}
