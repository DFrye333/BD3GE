#ifndef BD3GE_COLOR_H
#define BD3GE_COLOR_H

#include "../utility/vector.h"

namespace BD3GE {
	class Color {
		public:
			Color();
			Color(Vector3 rgb, float a);
			Color(Vector3 rgb);

			Vector3 rgb;
			float a;
	};
}

#endif // BD3GE_COLOR_H