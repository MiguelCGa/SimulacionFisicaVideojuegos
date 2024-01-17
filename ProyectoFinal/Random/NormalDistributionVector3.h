#pragma once

#include "DistributionVector3.h"

class NormalDistributionVector3 : public DistributionVector3<std::normal_distribution<>> {
public:
	NormalDistributionVector3(Vector3 const& mean, Vector3 const& dev);
};
