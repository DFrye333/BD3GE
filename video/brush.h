#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/renderable.h"
#include "../video/shader.h"
#include "../video/texture.h"

namespace BD3GE {
	class Brush : public Renderable {
		public:
			Brush();
			Brush(Vector3 position);
			virtual ~Brush();

			Texture* texture;
		protected:
	};

	class SquareBrush : public Brush {
		public:
			SquareBrush(Vector3 position, float width, float height, SimpleMaterial* simple_material);
			SquareBrush(Vector3 position, float width, float height, MappedMaterial* mapped_material);
	};

	class CircularBrush : public Brush {
		public:
			CircularBrush(Vector3 position, float radius, int resolution, SimpleMaterial* simple_material);
	};

	class BoxBrush : public Brush {
		public:
			BoxBrush(Vector3 position, Vector3 dimensions, SimpleMaterial* color);
	};
}

#endif // BD3GE_BRUSH_H