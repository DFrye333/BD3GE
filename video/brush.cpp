#include "brush.h"

namespace BD3GE {
	Brush::Brush() : texture(nullptr) {}

	Brush::Brush(Vector3 position) : Renderable(position), texture(nullptr) {}

	Brush::~Brush() {
		delete texture;
		texture = nullptr;
	}

	SquareBrush::SquareBrush(Vector3 position, float width, float height, SimpleMaterial* simpleMaterial) : Brush(position) {
		sizePerVertex = 6;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		// Top-left
		vbo[0] = (GLfloat)(-width / 2);		// Position X
		vbo[1] = (GLfloat)(height / 2);		// Position Y
		vbo[2] = (GLfloat)0;				// Position Z
		vbo[3] = 0;							// Normal X
		vbo[4] = 0;							// Normal Y
		vbo[5] = 1;							// Normal Z

		// Top-right
		vbo[6] = (GLfloat)(width / 2);
		vbo[7] = (GLfloat)(height / 2);
		vbo[8] = (GLfloat)0;
		vbo[9] = 0;
		vbo[10] = 0;
		vbo[11] = 1;

		// Bottom-right
		vbo[12] = (GLfloat)(width / 2);
		vbo[13] = (GLfloat)(-height / 2);
		vbo[14] = (GLfloat)0;
		vbo[15] = 0;
		vbo[16] = 0;
		vbo[17] = 1;

		// Bottom-left
		vbo[18] = (GLfloat)(-width / 2);
		vbo[19] = (GLfloat)(-height / 2);
		vbo[20] = (GLfloat)0;
		vbo[21] = 0;
		vbo[22] = 0;
		vbo[23] = 1;

		numIndices = 6;
		ibo = new GLuint[(GLuint)numIndices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		this->materials.push_back(simpleMaterial);

		setup();

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	SquareBrush::SquareBrush(Vector3 position, float width, float height, MappedMaterial* mappedMaterial) : Brush(position) {
		setupSquare(width, height);

		// Mapped material
		if (mappedMaterial != nullptr) {
			this->materials.push_back(mappedMaterial);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(1);
		}
	}

	void SquareBrush::setupSquare(float width, float height) {
		sizePerVertex = 5;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		// Top-left
		vbo[0] = (GLfloat)(-width / 2); // Position X
		vbo[1] = (GLfloat)(height / 2); // Position Y
		vbo[2] = (GLfloat)0;			// Position Z
		vbo[3] = 0.0f;					// Texture U
		vbo[4] = 1.0f;					// Texture V

		// Top-right
		vbo[5] = (GLfloat)(width / 2);
		vbo[6] = (GLfloat)(height / 2);
		vbo[7] = (GLfloat)0;
		vbo[8] = 1.0f;
		vbo[9] = 1.0f;

		// Bottom-right
		vbo[10] = (GLfloat)(width / 2);
		vbo[11] = (GLfloat)(-height / 2);
		vbo[12] = (GLfloat)0;
		vbo[13] = 1.0f;
		vbo[14] = 0.0f;

		// Bottom-left
		vbo[15] = (GLfloat)(-width / 2);
		vbo[16] = (GLfloat)(-height / 2);
		vbo[17] = (GLfloat)0;
		vbo[18] = 0.0f;
		vbo[19] = 0.0f;

		numIndices = 6;
		ibo = new GLuint[(GLuint)numIndices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		setup();
	}

	CircularBrush::CircularBrush(Vector3 position, float radius, int resolution, Color color) : Brush(position) {
		sizePerVertex = 10;
		numVertices = (4 * resolution) + 1;
		vbo = new GLfloat[sizePerVertex * GLuint(numVertices)];

		// Center
		vbo[0] = (GLfloat)0;
		vbo[1] = (GLfloat)0;
		vbo[2] = (GLfloat)0;
		vbo[3] = (GLfloat)color.rgb.v.c.r;
		vbo[4] = (GLfloat)color.rgb.v.c.g;
		vbo[5] = (GLfloat)color.rgb.v.c.b;
		vbo[6] = (GLfloat)color.a;
		vbo[7] = 0;
		vbo[8] = 0;
		vbo[9] = 1;

		// Circumference
		for (unsigned int i = 0; i < numVertices - 1; ++i) {
			vbo[(sizePerVertex * (i + 1)) + 0] = (GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 1] = (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 2] = (GLfloat)(0);
			vbo[(sizePerVertex * (i + 1)) + 3] = (GLfloat)color.rgb.v.c.r;
			vbo[(sizePerVertex * (i + 1)) + 4] = (GLfloat)color.rgb.v.c.g;
			vbo[(sizePerVertex * (i + 1)) + 5] = (GLfloat)color.rgb.v.c.b;
			vbo[(sizePerVertex * (i + 1)) + 6] = (GLfloat)color.a;
			vbo[(sizePerVertex * (i + 1)) + 7] = 0;
			vbo[(sizePerVertex * (i + 1)) + 8] = 0;
			vbo[(sizePerVertex * (i + 1)) + 9] = 1;
		}

		numIndices = 3 * (numVertices - 1);
		ibo = new GLuint[numIndices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)(numVertices - 1);
		for (int i = 1; i < numVertices - 1; ++i) {
			ibo[(3 * i) + 0] = (GLuint)0;
			ibo[(3 * i) + 1] = (GLuint)(numVertices - i);
			ibo[(3 * i) + 2] = (GLuint)(numVertices - i - 1);
		}

		setup();

		// Color
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Normals
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	CircularBrush::CircularBrush(Vector3 position, float radius, int resolution, SimpleMaterial* simpleMaterial) : Brush(position) {
		sizePerVertex = 6;
		numVertices = (4 * resolution) + 1;
		vbo = new GLfloat[sizePerVertex * GLuint(numVertices)];

		// Center
		vbo[0] = (GLfloat)0;
		vbo[1] = (GLfloat)0;
		vbo[2] = (GLfloat)0;
		vbo[3] = 0;
		vbo[4] = 0;
		vbo[5] = 1;

		// Circumference
		for (unsigned int i = 0; i < numVertices - 1; ++i) {
			vbo[(sizePerVertex * (i + 1)) + 0] = (GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 1] = (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 2] = (GLfloat)(0);
			vbo[(sizePerVertex * (i + 1)) + 3] = 0;
			vbo[(sizePerVertex * (i + 1)) + 4] = 0;
			vbo[(sizePerVertex * (i + 1)) + 5] = 1;
		}

		numIndices = 3 * (numVertices - 1);
		ibo = new GLuint[numIndices];
		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)(numVertices - 1);
		for (int i = 1; i < numVertices - 1; ++i) {
			ibo[(3 * i) + 0] = (GLuint)0;
			ibo[(3 * i) + 1] = (GLuint)(numVertices - i);
			ibo[(3 * i) + 2] = (GLuint)(numVertices - i - 1);
		}

		setup();

		this->materials.push_back(simpleMaterial);

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	BoxBrush::BoxBrush(Vector3 position, Vector3 dimensions, SimpleMaterial* simpleMaterial) : Brush(position) {
		this->materials.push_back(simpleMaterial);

		sizePerVertex = 6;
		numVertices = 8;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		float width = dimensions.v.g.x;
		float length = dimensions.v.g.y;
		float height = dimensions.v.g.z;

		// Near top-left
		vbo[0] = (GLfloat)(-width / 2);		// Position X
		vbo[1] = (GLfloat)(height / 2);		// Position Y
		vbo[2] = (GLfloat)(length / 2);		// Position Z
		vbo[3] = -1;						// Normal X
		vbo[4] = 1;							// Normal Y
		vbo[5] = 1;							// Normal Z

		// Near top-right
		vbo[6] = (GLfloat)(width / 2);
		vbo[7] = (GLfloat)(height / 2);
		vbo[8] = (GLfloat)(length / 2);
		vbo[9] = 1;
		vbo[10] = 1;
		vbo[11] = 1;

		// Near bottom-right
		vbo[12] = (GLfloat)(width / 2);
		vbo[13] = (GLfloat)(-height / 2);
		vbo[14] = (GLfloat)(length / 2);
		vbo[15] = 1;
		vbo[16] = -1;
		vbo[17] = 1;

		// Near bottom-left
		vbo[18] = (GLfloat)(-width / 2);
		vbo[19] = (GLfloat)(-height / 2);
		vbo[20] = (GLfloat)(length / 2);
		vbo[21] = -1;
		vbo[22] = -1;
		vbo[23] = 1;

		// Far top-left
		vbo[24] = (GLfloat)(-width / 2);
		vbo[25] = (GLfloat)(height / 2);
		vbo[26] = (GLfloat)(-length / 2);
		vbo[27] = -1;
		vbo[28] = 1;
		vbo[29] = -1;

		// Far top-right
		vbo[30] = (GLfloat)(width / 2);
		vbo[31] = (GLfloat)(height / 2);
		vbo[32] = (GLfloat)(-length / 2);
		vbo[33] = 1;
		vbo[34] = 1;
		vbo[35] = -1;

		// Far bottom-right
		vbo[36] = (GLfloat)(width / 2);
		vbo[37] = (GLfloat)(-height / 2);
		vbo[38] = (GLfloat)(-length / 2);
		vbo[39] = 1;
		vbo[40] = -1;
		vbo[41] = -1;

		// Far bottom-left
		vbo[42] = (GLfloat)(-width / 2);
		vbo[43] = (GLfloat)(-height / 2);
		vbo[44] = (GLfloat)(-length / 2);
		vbo[45] = -1;
		vbo[46] = -1;
		vbo[47] = -1;

		numIndices = 36;
		ibo = new GLuint[(GLuint)numIndices];

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

		// Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
}