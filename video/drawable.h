#ifndef BD3GE_DRAWABLE_H
#define BD3GE_DRAWABLE_H

#include <GL/glew.h>

#include "../utility/vector.h"

namespace BD3GE {
	class Drawable {
		public:
			virtual ~Drawable();

		//protected:
			GLfloat*	vertexPositionBuffer;
			GLuint*		indexPositionBuffer;
			GLuint		numVertices;
			GLuint		numIndices;
	};
}

#endif // BD3GE_DRAWABLE_H