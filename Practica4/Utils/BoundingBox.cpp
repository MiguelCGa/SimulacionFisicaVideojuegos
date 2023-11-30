#include "BoundingBox.h"

BoundingBox::BoundingBox() : 
	_min(1),
	_max(0),
	_origin(0) {
}

BoundingBox::BoundingBox(Vector3 origin, Vector3 offset) :
	_min(origin.x - offset.x, origin.y - offset.y, origin.z - offset.z),
	_max(origin.x + offset.x, origin.y + offset.y, origin.z + offset.z),
	_origin(origin){
}

BoundingBox::BoundingBox(Vector3 origin, float offset) : 
	BoundingBox(origin, Vector3(offset)) {
}

bool BoundingBox::contains(Vector3 const& pos) const noexcept {
	return
		(_min.x > _max.x && // limitless bounding box
		_min.y > _max.y &&
		_min.z > _max.z) ||
		(pos.x > _min.x &&
		pos.y > _min.y &&
		pos.z > _min.z &&
		pos.x < _max.x &&
		pos.y < _max.y &&
		pos.z < _max.z);
}

Vector3 BoundingBox::getOrigin() const {
	return _origin;
}

float BoundingBox::getWidth() const noexcept {
	return _max.x - _min.x;
}

float BoundingBox::getHeight() const noexcept {
	return _max.y - _min.y;
}

float BoundingBox::getDepth() const noexcept {
	return _max.z - _min.z;
}
