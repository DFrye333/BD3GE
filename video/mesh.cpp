#include "mesh.h"

namespace BD3GE {
	/*
	 *	Mesh class
	 */

	Mesh::Mesh(const aiMesh* mesh, Vector3 scale) : scale(1.0f) {
		g_log.write(BD3GE::LOG_TYPE::INFO, "Loading mesh with " + std::to_string(mesh->mNumVertices) + " vertices and " + std::to_string(mesh->mNumFaces) + " faces...");

		// Fills vertex position buffer.
		numVertices = mesh->mNumVertices;
		vertexPositionBuffer = new GLfloat[4 * numVertices];
		for (unsigned int i = 0; i < numVertices; ++i) {
			vertexPositionBuffer[(4 * i) + 0]	= (GLfloat)(mesh->mVertices[i].x * scale.v.g.x);
			vertexPositionBuffer[(4 * i) + 1]	= (GLfloat)(mesh->mVertices[i].y * scale.v.g.y);
			vertexPositionBuffer[(4 * i) + 2]	= (GLfloat)(mesh->mVertices[i].z * scale.v.g.z);
			vertexPositionBuffer[(4 * i) + 3]	= 1.0f;
		}

		// Determines the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		numIndices = 0;
		for (unsigned int i = 0; i < num_faces; ++i) {
			numIndices += mesh->mFaces[i].mNumIndices;
		}

		// Fills index position buffer.
		indexPositionBuffer = new GLuint[numIndices];
		for (unsigned int i = 0; i < num_faces; ++i) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
				indexPositionBuffer[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}
	}
}