#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../utility/color.h"
#include "../utility/vector.h"
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
			virtual void setup();
	};

	class SquareBrush : public Brush {
		public:
			SquareBrush(float width, float height, Shader* shader, Color color);
			SquareBrush(float width, float height, Shader* shader, Texture* texture);
	};

	class CircularBrush : public Brush {
		public:
			CircularBrush(float radius, int resolution, Shader* shader, Color color);
	};
}

#endif // BD3GE_BRUSH_H