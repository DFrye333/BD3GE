#include "brush.h"

namespace BD3GE {
	Brush::Brush() : RenderableUnit() {}

	Brush::Brush(Material* material) : RenderableUnit(material) {}

	RectangleBrush::RectangleBrush(Material* material, float width, float height) : Brush(material) {
		geometry.num_vertices = 4;
		geometry.vbo = new Vertex[geometry.num_vertices];

		// Top-left
		geometry.vbo[0] = Vertex(
			Vector3(-width / 2, height / 2, 0),	// Position
			Vector3(0, 0, 1),					// Normal
			Vector2(0, 1)						// Texture
		);

		// Top-right
		geometry.vbo[1] = Vertex(
			Vector3(width / 2, height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(1, 1)
		);

		// Bottom-right
		geometry.vbo[2] = Vertex(
			Vector3(width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(1, 0)
		);

		// Bottom-left
		geometry.vbo[3] = Vertex(
			Vector3(-width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(0, 0)
		);

		geometry.num_indices = 6;
		geometry.ibo = new GLuint[(GLuint)geometry.num_indices];
		geometry.ibo[0] = (GLuint)0;
		geometry.ibo[1] = (GLuint)1;
		geometry.ibo[2] = (GLuint)2;
		geometry.ibo[3] = (GLuint)0;
		geometry.ibo[4] = (GLuint)2;
		geometry.ibo[5] = (GLuint)3;
	}

	RectangleBrush::RectangleBrush(Material* material, float width, float height, TransformNode* transform_node) : RectangleBrush(material, width, height) {
		this->transform_node = transform_node;
	}

	CircularBrush::CircularBrush(Material* material, float radius, int resolution) : Brush(material) {
		geometry.num_vertices = (4 * resolution) + 1;
		geometry.vbo = new Vertex[geometry.num_vertices];

		// Center
		geometry.vbo[0] = Vertex(
			Vector3(0, 0, 0),
			Vector3(0, 0, 1),
			Vector2(0, 0)
		);

		// Circumference
		for (unsigned int i = 1; i < geometry.num_vertices; ++i) {
			geometry.vbo[i] = Vertex(
				Vector3((GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius), (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius), 0),
				Vector3(0, 0, 1),
				Vector2(0, 0)
			);
		}

		geometry.num_indices = 3 * (geometry.num_vertices - 1);
		geometry.ibo = new GLuint[geometry.num_indices];
		geometry.ibo[0] = (GLuint)0;
		geometry.ibo[1] = (GLuint)1;
		geometry.ibo[2] = (GLuint)(geometry.num_vertices - 1);
		for (int i = 1; i < geometry.num_vertices - 1; ++i) {
			geometry.ibo[(3 * i) + 0] = (GLuint)0;
			geometry.ibo[(3 * i) + 1] = (GLuint)(geometry.num_vertices - i);
			geometry.ibo[(3 * i) + 2] = (GLuint)(geometry.num_vertices - i - 1);
		}
	}

	BoxBrush::BoxBrush(Material* material, Vector3 dimensions) : Brush(material) {
		geometry.num_vertices = 8;
		geometry.vbo = new Vertex[geometry.num_vertices];

		float width = dimensions.v.g.x;
		float length = dimensions.v.g.y;
		float height = dimensions.v.g.z;

		// Near top-left
		geometry.vbo[0] = Vertex(
			Vector3(-width / 2, height / 2, length / 2),
			Vector3(-1, 1, 1),
			Vector2(0, 0)	// TODO (unified cubemaps): Set these up for a standard cubemap cross layout?
		);

		// Near top-right
		geometry.vbo[1] = Vertex(
			Vector3(width / 2, height / 2, length / 2),
			Vector3(1, 1, 1),
			Vector2(0, 0)
		);

		// Near bottom-right
		geometry.vbo[2] = Vertex(
			Vector3(width / 2, -height / 2, length / 2),
			Vector3(1, -1, 1),
			Vector2(0, 0)
		);

		// Near bottom-left
		geometry.vbo[3] = Vertex(
			Vector3(-width / 2, -height / 2, length / 2),
			Vector3(-1, -1, 1),
			Vector2(0, 0)
		);

		// Far top-left
		geometry.vbo[4] = Vertex(
			Vector3(-width / 2, height / 2, -length / 2),
			Vector3(-1, 1, -1),
			Vector2(0, 0)
		);

		// Far top-right
		geometry.vbo[5] = Vertex(
			Vector3(width / 2, height / 2, -length / 2),
			Vector3(1, 1, -1),
			Vector2(0, 0)
		);

		// Far bottom-right
		geometry.vbo[6] = Vertex(
			Vector3(width / 2, -height / 2, -length / 2),
			Vector3(1, -1, -1),
			Vector2(0, 0)
		);

		// Far bottom-left
		geometry.vbo[7] = Vertex(
			Vector3(-width / 2, -height / 2, -length / 2),
			Vector3(-1, -1, -1),
			Vector2(0, 0)
		);

		geometry.num_indices = 36;
		geometry.ibo = new GLuint[(GLuint)geometry.num_indices];

		// Near face
		geometry.ibo[0] = (GLuint)0;
		geometry.ibo[1] = (GLuint)1;
		geometry.ibo[2] = (GLuint)2;
		geometry.ibo[3] = (GLuint)0;
		geometry.ibo[4] = (GLuint)2;
		geometry.ibo[5] = (GLuint)3;

		// Left face
		geometry.ibo[6] = (GLuint)4;
		geometry.ibo[7] = (GLuint)0;
		geometry.ibo[8] = (GLuint)3;
		geometry.ibo[9] = (GLuint)4;
		geometry.ibo[10] = (GLuint)3;
		geometry.ibo[11] = (GLuint)7;

		// Far face
		geometry.ibo[12] = (GLuint)5;
		geometry.ibo[13] = (GLuint)4;
		geometry.ibo[14] = (GLuint)7;
		geometry.ibo[15] = (GLuint)5;
		geometry.ibo[16] = (GLuint)7;
		geometry.ibo[17] = (GLuint)6;

		// Right face
		geometry.ibo[18] = (GLuint)1;
		geometry.ibo[19] = (GLuint)5;
		geometry.ibo[20] = (GLuint)6;
		geometry.ibo[21] = (GLuint)1;
		geometry.ibo[22] = (GLuint)6;
		geometry.ibo[23] = (GLuint)2;

		// Top face
		geometry.ibo[24] = (GLuint)4;
		geometry.ibo[25] = (GLuint)5;
		geometry.ibo[26] = (GLuint)1;
		geometry.ibo[27] = (GLuint)4;
		geometry.ibo[28] = (GLuint)1;
		geometry.ibo[29] = (GLuint)0;

		// Bottom face
		geometry.ibo[30] = (GLuint)3;
		geometry.ibo[31] = (GLuint)2;
		geometry.ibo[32] = (GLuint)6;
		geometry.ibo[33] = (GLuint)3;
		geometry.ibo[34] = (GLuint)6;
		geometry.ibo[35] = (GLuint)7;
	}
}