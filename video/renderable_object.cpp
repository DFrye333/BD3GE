#include "renderable_object.h"

namespace BD3GE {
	RenderableObject::RenderableObject() : renderable(nullptr) {}

	RenderableObject::RenderableObject(Vector3 position, Renderable* renderable) : Object(position), renderable(renderable) {}

	RenderableObject::RenderableObject(Vector3 position, size_t renderable_id) : Object(position), renderable(nullptr), renderable_id(renderable_id) {}

	RenderableObject::RenderableObject(RenderableObject& other) : RenderableObject() {
		*this = other;
	}

	RenderableObject::~RenderableObject() {
		delete renderable;
		renderable = nullptr;
	}

	RenderableObject& RenderableObject::operator=(RenderableObject& other) {
		this->world_transform = other.world_transform;
		if (other.renderable) {
			delete this->renderable;
			this->renderable = new Renderable(*(other.renderable));
		}

		return *this;
	}
}