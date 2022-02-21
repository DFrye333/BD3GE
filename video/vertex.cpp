#include "vertex.h"

namespace BD3GE {
	Vertex::Vertex() : position(Vector3()), normal(Vector3()), uv(Vector2()) {}

	Vertex::Vertex(Vector3 position, Vector3 normal, Vector2 uv) : position(position), normal(normal), uv(uv) {}
}