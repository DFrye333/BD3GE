#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../system/api.h"
#include "../utility/transform.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/renderable.h"
#include "../video/shader.h"
#include "../video/texture.h"

namespace BD3GE {
	extern "C" class BD3GE_API Brush : public RenderableUnit {
		public:
			Brush();
			Brush(Material* material);
	};

	extern "C" class BD3GE_API RectangleBrush : public Brush {
		public:
			RectangleBrush(Material* material, float width, float height);
			RectangleBrush(Material* material, float width, float height, TransformNode* transform_node);
	};

	extern "C" class BD3GE_API CircularBrush : public Brush {
		public:
			CircularBrush(Material* material, float radius, int resolution);
	};

	extern "C" class BD3GE_API BoxBrush : public Brush {
		public:
			BoxBrush(Material* material, Vector3 dimensions);
	};
}

#endif // BD3GE_BRUSH_H