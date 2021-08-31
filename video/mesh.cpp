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

	void Mesh::setup() {
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

		// Textures
		/*if (texture != NULL && texture->pcData != NULL) {
			glGenTextures(1, &tboHandle);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tboHandle);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->mWidth, texture->mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->pcData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizePerVertex * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
			glEnableVertexAttribArray(2);
		}*/

		// Cleanup for VAO.
		/*glBindVertexArray(0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
	}
}