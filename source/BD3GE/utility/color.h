#ifndef BD3GE_COLOR_H
#define BD3GE_COLOR_H

#include <algorithm>

#include "../system/api.h"
#include "../utility/vector.h"

namespace BD3GE {
	class BD3GE_API Color {
		public:
			Color();
			Color(Vector3 rgb, float a);
			Color(Vector3 rgb);
			Color(int red, int green, int blue, float alpha);
			Color(int red, int green, int blue);
			friend std::ostream& operator<<(std::ostream& out, const Color& color);

			Vector3 rgb;
			float a;
	};
}

#endif // BD3GE_COLOR_H