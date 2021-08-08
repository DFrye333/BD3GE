#include "drawable.h"

namespace BD3GE {
	Drawable::~Drawable() {
		delete[] vertexPositionBuffer;
		vertexPositionBuffer = NULL;

		delete[] indexPositionBuffer;
		indexPositionBuffer = NULL;
	}
}