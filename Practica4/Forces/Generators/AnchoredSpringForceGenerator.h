#pragma once
#include "../ForceGenerator.h"

class AnchoredSpringForceGenerator : public ForceGenerator {
public:
	AnchoredSpringForceGenerator(double k, double resting_length, Vector3 const& anchorPoint);

	bool updateForce(Particle* p) override;

protected:
	Vector3 _anchorPoint;
	double _k, _resting_length;
};