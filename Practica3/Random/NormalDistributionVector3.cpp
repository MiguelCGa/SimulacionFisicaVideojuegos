#include "NormalDistributionVector3.h"


NormalDistributionVector3::NormalDistributionVector3(Vector3 const& mean, Vector3 const& dev) :
	DistributionVector3(
		std::normal_distribution<>::param_type(mean.x, dev.x),
		std::normal_distribution<>::param_type(mean.y, dev.y),
		std::normal_distribution<>::param_type(mean.z, dev.z)) {
}
