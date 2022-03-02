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
	class Brush : public RenderableUnit {
		public:
			Brush();
			Brush(Material* material);
	};

	class RectangleBrush : public Brush {
		public:
			RectangleBrush(Material* material, Vector3 position, float width, float height);
	};

	class CircularBrush : public Brush {
		public:
			CircularBrush(Material* material, Vector3 position, float radius, int resolution);
	};

	class BoxBrush : public Brush {
		public:
			BoxBrush(Material* material, Vector3 position, Vector3 dimensions);
	};
}

#endif // BD3GE_BRUSH_H