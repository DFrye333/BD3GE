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

	Color::Color(int red, int green, int blue, float alpha) {
		this->rgb = Vector3(std::clamp(red, 0, 255), std::clamp(green, 0, 255), std::clamp(blue, 0, 255));
		this->a = alpha;
	}

	Color::Color(int red, int green, int blue) : Color(red, green, blue, 1.0f) {}

	std::ostream& operator<<(std::ostream& out, const Color& color) {
		return out << "(" << color.rgb.v.c.r << ", " << color.rgb.v.c.g << ", " << color.rgb.v.c.b << ", " << color.a << ")";
	}
}