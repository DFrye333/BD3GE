#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../utility/color.h"
#include "../utility/vector.h"
#include "../video/renderable.h"

namespace BD3GE {
	class Brush : public Renderable {
		public:
			Brush();
			virtual void setup();
	};

	class SquareBrush : public Brush {
		public:
			SquareBrush(float width, float height, Color color);
	};

	class CircularBrush : public Brush {
		public:
			CircularBrush(float radius, int resolution, Color color);
	};
}

#endif // BD3GE_BRUSH_H