#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../utility/color.h"
#include "../utility/vector.h"
#include "../video/material.h"
#include "../video/renderable.h"
#include "../video/shader.h"
#include "../video/texture.h"

namespace BD3GE {
	class Brush : public Renderable {
		public:
			Brush();
			virtual ~Brush();

			Texture* texture;
		protected:
	};

	class SquareBrush : public Brush {
		public:
			SquareBrush(float width, float height, Shader* shader, Color color);
			SquareBrush(float width, float height, Shader* shader, Texture* texture);
			SquareBrush(float width, float height, Shader* shader, MappedMaterial* mappedMaterial);
	};

	class CircularBrush : public Brush {
		public:
			CircularBrush(float radius, int resolution, Shader* shader, Color color);
	};
}

#endif // BD3GE_BRUSH_H