#include "brush.h"

namespace BD3GE {
	SquareBrush::SquareBrush(float width, float height) {
		numVertices = 4;
		vertexPositionBuffer = new GLfloat[4 * numVertices];

		vertexPositionBuffer[0] = (GLfloat)(0);
		vertexPositionBuffer[1] = (GLfloat)(0);
		vertexPositionBuffer[2] = (GLfloat)(0);
		vertexPositionBuffer[3] = 1.0f;

		vertexPositionBuffer[4] = (GLfloat)(width);
		vertexPositionBuffer[5] = (GLfloat)(0);
		vertexPositionBuffer[6] = (GLfloat)(0);
		vertexPositionBuffer[7] = 1.0f;

		vertexPositionBuffer[8] = (GLfloat)(width);
		vertexPositionBuffer[9] = (GLfloat)(-height);
		vertexPositionBuffer[10] = (GLfloat)(0);
		vertexPositionBuffer[11] = 1.0f;

		vertexPositionBuffer[12] = (GLfloat)(0);
		vertexPositionBuffer[13] = (GLfloat)(-height);
		vertexPositionBuffer[14] = (GLfloat)(0);
		vertexPositionBuffer[15] = 1.0f;

		numIndices = 6;
		indexPositionBuffer = new GLuint[numIndices];

		indexPositionBuffer[0] = 0;
		indexPositionBuffer[1] = 1;
		indexPositionBuffer[2] = 2;
		indexPositionBuffer[3] = 0;
		indexPositionBuffer[4] = 2;
		indexPositionBuffer[5] = 3;
	}

	CircularBrush::CircularBrush(float radius, int resolution) {
		numVertices = (4 * resolution) + 1;
		vertexPositionBuffer = new GLfloat[4 * numVertices];

		// Center
		vertexPositionBuffer[0] = (GLfloat)(0);
		vertexPositionBuffer[1] = (GLfloat)(0);
		vertexPositionBuffer[2] = (GLfloat)(0);
		vertexPositionBuffer[3] = 1.0f;

		// Circumference
		for (unsigned int i = 0; i < numVertices - 1; ++i) {
			vertexPositionBuffer[(4 * (i + 1)) + 0] = (GLfloat)(cos(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vertexPositionBuffer[(4 * (i + 1)) + 1] = (GLfloat)(sin(i * ((std::numbers::pi / 2) / resolution)) * radius);
			vertexPositionBuffer[(4 * (i + 1)) + 2] = (GLfloat)(0);
			vertexPositionBuffer[(4 * (i + 1)) + 3] = 1.0f;
		}

		numIndices = 3 * (numVertices - 1);
		indexPositionBuffer = new GLuint[numIndices];
		indexPositionBuffer[0] = 0;
		indexPositionBuffer[1] = 1;
		indexPositionBuffer[2] = numVertices - 1;
		for (int i = 1; i < numVertices - 1; ++i) {
			indexPositionBuffer[(3 * i) + 0] = 0;
			indexPositionBuffer[(3 * i) + 1] = numVertices - i;
			indexPositionBuffer[(3 * i) + 2] = numVertices - i - 1;
		}
	}
}