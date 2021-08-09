#ifndef BD3GE_BRUSH_H
#define BD3GE_BRUSH_H

#include <cmath>
#include <numbers>

#include "../utility/vector.h"
#include "../video/drawable.h"

namespace BD3GE {
	class SquareBrush : public Drawable {
		public:
			SquareBrush(float width, float height);
	};

	class CircularBrush : public Drawable {
		public:
			CircularBrush(float radius, int resolution);
	};
}

#endif