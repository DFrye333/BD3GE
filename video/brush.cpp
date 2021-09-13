#include "brush.h"

namespace BD3GE {
	Brush::Brush() : texture(nullptr) {}

	Brush::~Brush() {
		delete texture;
		texture = nullptr;
	}

	void Brush::setup() {
		// Generate VAO.
		glGenVertexArrays(1, &vaoHandle);

		// Generate VBOs.
		GLuint vboHandle, iboHandle;
		glGenBuffers(1, &vboHandle);
		glGenBuffers(1, &iboHandle);

		// Setup for VAO.
		glBindVertexArray(vaoHandle);

		glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
		glBufferData(GL_ARRAY_BUFFER, sizePerVertex * numVertices * sizeof(GLfloat), vbo, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboHandle);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), ibo, GL_STATIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);
	}

	SquareBrush::SquareBrush(float width, float height, Shader* shader, Color color) {
		sizePerVertex = 10;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		// Top-left
		vbo[0] = (GLfloat)(-width / 2);
		vbo[1] = (GLfloat)(height / 2);
		vbo[2] = (GLfloat)0;
		vbo[3] = (GLfloat)color.rgb.v.c.r;
		vbo[4] = (GLfloat)color.rgb.v.c.g;
		vbo[5] = (GLfloat)color.rgb.v.c.b;
		vbo[6] = (GLfloat)color.a;
		vbo[7] = 0;
		vbo[8] = 0;
		vbo[9] = 1;

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
		vbo[0] = (GLfloat)(-width / 2);
		vbo[1] = (GLfloat)(height / 2);
		vbo[2] = (GLfloat)0;
		vbo[3] = 0.0f;
		vbo[4] = 1.0f;

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

		// Textures
		if (texture != NULL && texture->data != NULL) {
			glGenTextures(1, &tboHandle);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tboHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
			glGenerateMipmap(GL_TEXTURE_2D);

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
}