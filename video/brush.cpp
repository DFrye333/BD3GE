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

	SquareBrush::SquareBrush(float width, float height, Color color) {
		sizePerVertex = 6;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		vbo[0] = (GLfloat)0;
		vbo[1] = (GLfloat)0;
		vbo[2] = (GLfloat)0;
		vbo[3] = (GLfloat)color.rgb.v.c.r;
		vbo[4] = (GLfloat)color.rgb.v.c.g;
		vbo[5] = (GLfloat)color.rgb.v.c.b;

		vbo[6] = (GLfloat)width;
		vbo[7] = (GLfloat)0;
		vbo[8] = (GLfloat)0;
		vbo[9] = (GLfloat)color.rgb.v.c.r;
		vbo[10] = (GLfloat)color.rgb.v.c.g;
		vbo[11] = (GLfloat)color.rgb.v.c.b;

		vbo[12] = (GLfloat)width;
		vbo[13] = (GLfloat)(-height);
		vbo[14] = (GLfloat)0;
		vbo[15] = (GLfloat)color.rgb.v.c.r;
		vbo[16] = (GLfloat)color.rgb.v.c.g;
		vbo[17] = (GLfloat)color.rgb.v.c.b;

		vbo[18] = (GLfloat)0;
		vbo[19] = (GLfloat)(-height);
		vbo[20] = (GLfloat)0;
		vbo[21] = (GLfloat)color.rgb.v.c.r;
		vbo[22] = (GLfloat)color.rgb.v.c.g;
		vbo[23] = (GLfloat)color.rgb.v.c.b;

		numIndices = 6;
		ibo = new GLuint[(GLuint)numIndices];

		ibo[0] = (GLuint)0;
		ibo[1] = (GLuint)1;
		ibo[2] = (GLuint)2;
		ibo[3] = (GLuint)0;
		ibo[4] = (GLuint)2;
		ibo[5] = (GLuint)3;

		setup();

		// Colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	SquareBrush::SquareBrush(float width, float height, Shader* shader, Texture* texture) {
		sizePerVertex = 5;
		numVertices = 4;
		vbo = new GLfloat[sizePerVertex * (GLuint)numVertices];

		vbo[0] = (GLfloat)0;
		vbo[1] = (GLfloat)0;
		vbo[2] = (GLfloat)0;
		vbo[3] = 0.0f;
		vbo[4] = 1.0f;

		vbo[5] = (GLfloat)width;
		vbo[6] = (GLfloat)0;
		vbo[7] = (GLfloat)0;
		vbo[8] = 1.0f;
		vbo[9] = 1.0f;

		vbo[10] = (GLfloat)width;
		vbo[11] = (GLfloat)(-height);
		vbo[12] = (GLfloat)0;
		vbo[13] = 1.0f;
		vbo[14] = 0.0f;

		vbo[15] = (GLfloat)0;
		vbo[16] = (GLfloat)(-height);
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

	CircularBrush::CircularBrush(float radius, int resolution, Color color) {
		sizePerVertex = 6;
		numVertices = (4 * resolution) + 1;
		vbo = new GLfloat[sizePerVertex * GLuint(numVertices)];

		// Center
		vbo[0] = (GLfloat)0;
		vbo[1] = (GLfloat)0;
		vbo[2] = (GLfloat)0;
		vbo[3] = (GLfloat)color.rgb.v.c.r;
		vbo[4] = (GLfloat)color.rgb.v.c.g;
		vbo[5] = (GLfloat)color.rgb.v.c.b;

		// Circumference
		for (unsigned int i = 0; i < numVertices - 1; ++i) {
			vbo[(sizePerVertex * (i + 1)) + 0] = (GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 1] = (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vbo[(sizePerVertex * (i + 1)) + 2] = (GLfloat)(0);
			vbo[(sizePerVertex * (i + 1)) + 3] = (GLfloat)color.rgb.v.c.r;
			vbo[(sizePerVertex * (i + 1)) + 4] = (GLfloat)color.rgb.v.c.g;
			vbo[(sizePerVertex * (i + 1)) + 5] = (GLfloat)color.rgb.v.c.b;
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
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}
}