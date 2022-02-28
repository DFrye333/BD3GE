#ifndef BD3GE_VERTEX_H
#define BD3GE_VERTEX_H

#include "../utility/vector.h"

namespace BD3GE {
	class Vertex {
		public:
			Vertex();
			Vertex(Vector3 position, Vector3 normal, Vector2 uv);

			Vector3 position;
			Vector3 normal;
			Vector2 uv;
	};
}

#endif // BD3GE_VERTEX_H