#include "color.h"

namespace BD3GE {
	Color::Color() {
		this->rgb = Vector3(0.0f, 0.0f, 0.0f);
		this->a = 1.0f;
	}

	Color::Color(Vector3 rgb, float a) {
		this->rgb = rgb;
		this->a = a;
	}

	Color::Color(Vector3 rgb) : Color(rgb, 1.0f) {}
}