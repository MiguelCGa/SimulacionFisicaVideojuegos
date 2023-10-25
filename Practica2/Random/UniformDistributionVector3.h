#pragma once

#include "DistributionVector3.h"

class UniformDistributionVector3 : public DistributionVector3<std::uniform_real_distribution<>> {
public:
	UniformDistributionVector3(Vector3 const& mean, Vector3 const& width);
};