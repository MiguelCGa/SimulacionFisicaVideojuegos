#pragma once
#include "../ForceGenerator.h"

class AnchoredSpringForceGenerator : public ForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint);
	AnchoredSpringForceGenerator(double k, double resting_length, const Vector3& anchorPoint, bool showAnchor);
	~AnchoredSpringForceGenerator();


	inline double getK() const { return _k; }
	inline void setK(double k) { if (k > 0.0) _k = k; }

protected:
	void applyForce(Particle* p) override;

	RenderItem* item;

	physx::PxTransform _anchorPoint;
	double _k, _resting_length;
};