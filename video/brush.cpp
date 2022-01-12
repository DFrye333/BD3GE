#include "brush.h"

namespace BD3GE {
	Brush::Brush() : texture(nullptr) {}

	Brush::~Brush() {
		delete texture;
		texture = nullptr;
	}

	SquareBrush::SquareBrush(float width, float height, Shader* shader, Color color) {
		sizePerVertex = 10;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		// Top-left
		vbo[0] = (GLfloat)(-width / 2);		// Position X
		vbo[1] = (GLfloat)(height / 2);		// Position Y
		vbo[2] = (GLfloat)0;				// Position Z
		vbo[3] = (GLfloat)color.rgb.v.c.r;	// Color R
		vbo[4] = (GLfloat)color.rgb.v.c.g;	// Color G
		vbo[5] = (GLfloat)color.rgb.v.c.b;	// Color B
		vbo[6] = (GLfloat)color.a;			// Color A
		vbo[7] = 0;							// Normal X
		vbo[8] = 0;							// Normal Y
		vbo[9] = 1;							// Normal Z

		// Top-right
		vbo[10] = (GLfloat)(width / 2);
		vbo[11] = (GLfloat)(height / 2);
		vbo[12] = (GLfloat)0;
		vbo[13] = (GLfloat)color.rgb.v.c.r;
		vbo[14] = (GLfloat)color.rgb.v.c.g;
		vbo[15] = (GLfloat)color.rgb.v.c.b;
		vbo[16] = (GLfloat)color.a;
		vbo[17] = 0;
		vbo[18] = 0;
		vbo[19] = 1;

		// Bottom-right
		vbo[20] = (GLfloat)(width / 2);
		vbo[21] = (GLfloat)(-height / 2);
		vbo[22] = (GLfloat)0;
		vbo[23] = (GLfloat)color.rgb.v.c.r;
		vbo[24] = (GLfloat)color.rgb.v.c.g;
		vbo[25] = (GLfloat)color.rgb.v.c.b;
		vbo[26] = (GLfloat)color.a;
		vbo[27] = 0;
		vbo[28] = 0;
		vbo[29] = 1;

		// Bottom-left
		vbo[30] = (GLfloat)(-width / 2);
		vbo[31] = (GLfloat)(-height / 2);
		vbo[32] = (GLfloat)0;
		vbo[33] = (GLfloat)color.rgb.v.c.r;
		vbo[34] = (GLfloat)color.rgb.v.c.g;
		vbo[35] = (GLfloat)color.rgb.v.c.b;
		vbo[36] = (GLfloat)color.a;
		vbo[37] = 0;
		vbo[38] = 0;
		vbo[39] = 1;

		numIndices = 6;
		ibo = new GLuint[(GLuint)numIndices];

		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		this->shader = shader;

		setup();

		// Colors
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Normals
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	SquareBrush::SquareBrush(float width, float height, Shader* shader, Texture* texture) {
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

		this->shader = shader;
		this->texture = texture;

		setup();

		// Texture
		if (texture != NULL && texture->data != NULL) {
			addTexture(GL_TEXTURE0, texture);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
	}

	SquareBrush::SquareBrush(float width, float height, Shader* shader, MappedMaterial* mappedMaterial) {
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

		this->shader = shader;

		setup();

		// Mapped material
		if (mappedMaterial != nullptr) {
			setMaterial(mappedMaterial);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}
	}

	CircularBrush::CircularBrush(float radius, int resolution, Shader* shader, Color color) {
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

		this->shader = shader;

		setup();

		// Colors
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Normals
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	BoxBrush::BoxBrush(Vector3 dimensions, Shader* shader, Color color) {
		this->shader = shader;

		sizePerVertex = 10;
		numVertices = 8;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		float width = dimensions.v.g.x;
		float length = dimensions.v.g.y;
		float height = dimensions.v.g.z;

		// Near top-left
		vbo[0] = (GLfloat)(-width / 2);		// Position X
		vbo[1] = (GLfloat)(height / 2);		// Position Y
		vbo[2] = (GLfloat)(length / 2);		// Position Z
		vbo[3] = (GLfloat)color.rgb.v.c.r;	// Color R
		vbo[4] = (GLfloat)color.rgb.v.c.g;	// Color G
		vbo[5] = (GLfloat)color.rgb.v.c.b;	// Color B
		vbo[6] = (GLfloat)color.a;			// Color A
		vbo[7] = -1;						// Normal X
		vbo[8] = 1;							// Normal Y
		vbo[9] = 1;							// Normal Z

		// Near top-right
		vbo[10] = (GLfloat)(width / 2);
		vbo[11] = (GLfloat)(height / 2);
		vbo[12] = (GLfloat)(length / 2);
		vbo[13] = (GLfloat)color.rgb.v.c.r;
		vbo[14] = (GLfloat)color.rgb.v.c.g;
		vbo[15] = (GLfloat)color.rgb.v.c.b;
		vbo[16] = (GLfloat)color.a;
		vbo[17] = 1;
		vbo[18] = 1;
		vbo[19] = 1;

		// Near bottom-right
		vbo[20] = (GLfloat)(width / 2);
		vbo[21] = (GLfloat)(-height / 2);
		vbo[22] = (GLfloat)(length / 2);
		vbo[23] = (GLfloat)color.rgb.v.c.r;
		vbo[24] = (GLfloat)color.rgb.v.c.g;
		vbo[25] = (GLfloat)color.rgb.v.c.b;
		vbo[26] = (GLfloat)color.a;
		vbo[27] = 1;
		vbo[28] = -1;
		vbo[29] = 1;

		// Near bottom-left
		vbo[30] = (GLfloat)(-width / 2);
		vbo[31] = (GLfloat)(-height / 2);
		vbo[32] = (GLfloat)(length / 2);
		vbo[33] = (GLfloat)color.rgb.v.c.r;
		vbo[34] = (GLfloat)color.rgb.v.c.g;
		vbo[35] = (GLfloat)color.rgb.v.c.b;
		vbo[36] = (GLfloat)color.a;
		vbo[37] = -1;
		vbo[38] = -1;
		vbo[39] = 1;

		// Far top-left
		vbo[40] = (GLfloat)(-width / 2);
		vbo[41] = (GLfloat)(height / 2);
		vbo[42] = (GLfloat)(-length / 2);
		vbo[43] = (GLfloat)color.rgb.v.c.r;
		vbo[44] = (GLfloat)color.rgb.v.c.g;
		vbo[45] = (GLfloat)color.rgb.v.c.b;
		vbo[46] = (GLfloat)color.a;
		vbo[47] = -1;
		vbo[48] = 1;
		vbo[49] = -1;

		// Far top-right
		vbo[50] = (GLfloat)(width / 2);
		vbo[51] = (GLfloat)(height / 2);
		vbo[52] = (GLfloat)(-length / 2);
		vbo[53] = (GLfloat)color.rgb.v.c.r;
		vbo[54] = (GLfloat)color.rgb.v.c.g;
		vbo[55] = (GLfloat)color.rgb.v.c.b;
		vbo[56] = (GLfloat)color.a;
		vbo[57] = 1;
		vbo[58] = 1;
		vbo[59] = -1;

		// Far bottom-right
		vbo[60] = (GLfloat)(width / 2);
		vbo[61] = (GLfloat)(-height / 2);
		vbo[62] = (GLfloat)(-length / 2);
		vbo[63] = (GLfloat)color.rgb.v.c.r;
		vbo[64] = (GLfloat)color.rgb.v.c.g;
		vbo[65] = (GLfloat)color.rgb.v.c.b;
		vbo[66] = (GLfloat)color.a;
		vbo[67] = 1;
		vbo[68] = -1;
		vbo[69] = -1;

		// Far bottom-left
		vbo[70] = (GLfloat)(-width / 2);
		vbo[71] = (GLfloat)(-height / 2);
		vbo[72] = (GLfloat)(-length / 2);
		vbo[73] = (GLfloat)color.rgb.v.c.r;
		vbo[74] = (GLfloat)color.rgb.v.c.g;
		vbo[75] = (GLfloat)color.rgb.v.c.b;
		vbo[76] = (GLfloat)color.a;
		vbo[77] = -1;
		vbo[78] = -1;
		vbo[79] = -1;

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

		// Colors
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Normals
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(7 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}
}