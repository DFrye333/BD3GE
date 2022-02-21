#include "brush.h"

namespace BD3GE {
	Brush::Brush() : texture(nullptr) {}

	Brush::Brush(Vector3 position) : Renderable(position), texture(nullptr) {}

	Brush::~Brush() {
		delete texture;
		texture = nullptr;
	}

	SquareBrush::SquareBrush(Vector3 position, float width, float height, SimpleMaterial* simple_material) : Brush(position) {
		num_vertices = 4;
		vbo = new Vertex[num_vertices];

		// Top-left
		vbo[0] = Vertex(
			Vector3(-width / 2, height / 2, 0),	// Position
			Vector3(0, 0, 1),					// Normal
			Vector2()							// Texture
		);
		// Top-right
		vbo[1] = Vertex(
			Vector3(width / 2, height / 2, 0),
			Vector3(0, 0, 1),
			Vector2()
		);
		// Bottom-right
		vbo[2] = Vertex(
			Vector3(-width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2()
		);
		// Bottom-left
		vbo[3] = Vertex(
			Vector3(-width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2()
		);

		num_indices = 6;
		ibo = new GLuint[(GLuint)num_indices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		this->materials.push_back(simple_material);

		setup();
	}

	SquareBrush::SquareBrush(Vector3 position, float width, float height, MappedMaterial* mapped_material) : Brush(position) {
		num_vertices = 4;
		vbo = new Vertex[num_vertices];
		
		// Top-left
		vbo[0] = Vertex(
			Vector3(-width / 2, height / 2, 0),	// Position
			Vector3(0, 0, 1),					// Normal
			Vector2(0, 1)						// Texture
		);

		// Top-right
		vbo[1] = Vertex(
			Vector3(width / 2, height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(1, 1)
		);

		// Bottom-right
		vbo[2] = Vertex(
			Vector3(width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(1, 0)
		);

		// Bottom-left
		vbo[3] = Vertex(
			Vector3(-width / 2, -height / 2, 0),
			Vector3(0, 0, 1),
			Vector2(0, 0)
		);

		num_indices = 6;
		ibo = new GLuint[(GLuint)num_indices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		setup();

		this->materials.push_back(mapped_material);
	}

	CircularBrush::CircularBrush(Vector3 position, float radius, int resolution, SimpleMaterial* simple_material) : Brush(position) {
		this->materials.push_back(simple_material);

		num_vertices = (4 * resolution) + 1;
		vbo = new Vertex[num_vertices];

		// Center
		vbo[0] = Vertex(
			Vector3(0, 0, 0),
			Vector3(0, 0, 1),
			Vector2(0, 0)
		);

		// Circumference
		for (unsigned int i = 1; i < num_vertices; ++i) {
			vbo[i] = Vertex(
				Vector3((GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius), (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius), 0),
				Vector3(0, 0, 1),
				Vector2(0, 0)
			);
		}

		num_indices = 3 * (num_vertices - 1);
		ibo = new GLuint[num_indices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)(num_vertices - 1);
		for (int i = 1; i < num_vertices - 1; ++i) {
			ibo[(3 * i) + 0] = (GLuint)0;
			ibo[(3 * i) + 1] = (GLuint)(num_vertices - i);
			ibo[(3 * i) + 2] = (GLuint)(num_vertices - i - 1);
		}

		setup();
	}

	BoxBrush::BoxBrush(Vector3 position, Vector3 dimensions, SimpleMaterial* simple_material) : Brush(position) {
		this->materials.push_back(simple_material);

		num_vertices = 8;
		vbo = new Vertex[num_vertices];

		float width = dimensions.v.g.x;
		float length = dimensions.v.g.y;
		float height = dimensions.v.g.z;

		// Near top-left
		vbo[0] = Vertex(
			Vector3(-width / 2, height / 2, length / 2),
			Vector3(-1, 1, 1),
			Vector2(0, 0)
		);

		// Near top-right
		vbo[1] = Vertex(
			Vector3(width / 2, height / 2, length / 2),
			Vector3(1, 1, 1),
			Vector2(0, 0)
		);

		// Near bottom-right
		vbo[2] = Vertex(
			Vector3(width / 2, -height / 2, length / 2),
			Vector3(1, -1, 1),
			Vector2(0, 0)
		);

		// Near bottom-left
		vbo[3] = Vertex(
			Vector3(-width / 2, -height / 2, length / 2),
			Vector3(-1, -1, 1),
			Vector2(0, 0)
		);

		// Far top-left
		vbo[4] = Vertex(
			Vector3(-width / 2, height / 2, -length / 2),
			Vector3(-1, 1, -1),
			Vector2(0, 0)
		);

		// Far top-right
		vbo[5] = Vertex(
			Vector3(width / 2, height / 2, -length / 2),
			Vector3(1, 1, -1),
			Vector2(0, 0)
		);

		// Far bottom-right
		vbo[6] = Vertex(
			Vector3(width / 2, -height / 2, -length / 2),
			Vector3(1, -1, -1),
			Vector2(0, 0)
		);

		// Far bottom-left
		vbo[7] = Vertex(
			Vector3(-width / 2, -height / 2, -length / 2),
			Vector3(-1, -1, -1),
			Vector2(0, 0)
		);

		num_indices = 36;
		ibo = new GLuint[(GLuint)num_indices];

		// Near face
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		// Left face
		ibo[6] = (GLuint)4;
		ibo[7] = (GLuint)0;
		ibo[8] = (GLuint)3;
		ibo[9] = (GLuint)4;
		ibo[10] = (GLuint)3;
		ibo[11] = (GLuint)7;

		// Far face
		ibo[12] = (GLuint)5;
		ibo[13] = (GLuint)4;
		ibo[14] = (GLuint)7;
		ibo[15] = (GLuint)5;
		ibo[16] = (GLuint)7;
		ibo[17] = (GLuint)6;

		// Right face
		ibo[18] = (GLuint)1;
		ibo[19] = (GLuint)5;
		ibo[20] = (GLuint)6;
		ibo[21] = (GLuint)1;
		ibo[22] = (GLuint)6;
		ibo[23] = (GLuint)2;

		// Top face
		ibo[24] = (GLuint)4;
		ibo[25] = (GLuint)5;
		ibo[26] = (GLuint)1;
		ibo[27] = (GLuint)4;
		ibo[28] = (GLuint)1;
		ibo[29] = (GLuint)0;

		// Bottom face
		ibo[30] = (GLuint)3;
		ibo[31] = (GLuint)2;
		ibo[32] = (GLuint)6;
		ibo[33] = (GLuint)3;
		ibo[34] = (GLuint)6;
		ibo[35] = (GLuint)7;

		setup();
	}
}