#pragma once
#include "../ForceGenerator.h"

class AnchoredSpringForceGenerator : public ForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint);
	AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint, bool showAnchor);
	~AnchoredSpringForceGenerator();
	bool updateForce(Particle* p) override;

protected:
	RenderItem* item;

	physx::PxTransform _anchorPoint;
	double _k, _resting_length;
};