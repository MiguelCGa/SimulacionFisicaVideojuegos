#include "BuoyancyForceGenerator.h"

BuoyancyForceGenerator::BuoyancyForceGenerator(BoundingBox area, float d) :
	ForceGenerator(-1.0),
	_height(area.getHeight()),
	_volume(area.getWidth()* area.getHeight()* area.getDepth()),
	_fluid_density(d),
	_area(area),
	_pos(area.getOrigin()),
	_item(new RenderItem(CreateShape(physx::PxBoxGeometry(area.getWidth(), area.getHeight(), area.getDepth())),	&_pos, Vector4(0, 0, 1, 0.1))),

	_gravity(9.8f) {
}

BuoyancyForceGenerator::~BuoyancyForceGenerator() {
	delete _item;
}

bool BuoyancyForceGenerator::updateForce(Particle* p) {
	if (!_area.contains(p->getPosition())) return isAlive();

	const float object_height = p->getHeight();

	const float fluid_top = _pos.p.y + _height / 2.0f;
	const float object_bottom = p->getPosition().y - object_height / 2.0f;
	
	float immersed_height = fluid_top - object_bottom;

	if (immersed_height < 0.0f) immersed_height = 0.0f;
	else if (immersed_height > object_height) immersed_height = 1.0f;
	else immersed_height /= object_height;

	const Vector3 force (0, p->getSection() * immersed_height * _fluid_density * _gravity, 0);

	p->addForce(force);

	return isAlive();
}
