#include "mesh.h"

namespace BD3GE {
	Mesh::Mesh(const aiMesh* mesh, aiTexture* texture, Shader* shader, Vector3 scale) : Renderable(shader) {
		g_log.write(BD3GE::LOG_TYPE::INFO, "Loading mesh with " + std::to_string(mesh->mNumVertices) + " vertices and " + std::to_string(mesh->mNumFaces) + " faces...");

		// Fill the VBO.
		numVertices = mesh->mNumVertices;
		sizePerVertex = 5;
		vbo = new GLfloat[sizePerVertex * numVertices];
		for (unsigned int i = 0; i < numVertices; ++i) {
			vbo[(sizePerVertex * i) + 0] = (GLfloat)(mesh->mVertices[i].x * scale.v.g.x);
			vbo[(sizePerVertex * i) + 1] = (GLfloat)(mesh->mVertices[i].y * scale.v.g.y);
			vbo[(sizePerVertex * i) + 2] = (GLfloat)(mesh->mVertices[i].z * scale.v.g.z);
			vbo[(sizePerVertex * i) + 3] = (GLfloat)(mesh->mTextureCoords[0][i].x);
			vbo[(sizePerVertex * i) + 4] = (GLfloat)(mesh->mTextureCoords[0][i].y);
		}

		// Determines the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		numIndices = 0;
		for (unsigned int i = 0; i < num_faces; ++i) {
			numIndices += mesh->mFaces[i].mNumIndices;
		}

		// Fills the IBO.
		ibo = new GLuint[numIndices];
		for (unsigned int i = 0; i < num_faces; ++i) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
				ibo[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}

		setup();
	}

	Mesh::~Mesh() {
		// TODO: This is an aiMesh*, which is owned by an aiScene*
		/*delete texture;
		texture = nullptr;*/
	}
}