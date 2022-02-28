#include "mesh.h"

namespace BD3GE {
	Mesh::Mesh() : RenderableUnit() {}

	Mesh::Mesh(Material* material) : RenderableUnit(material) {}

	Mesh::Mesh(Material* material, const aiMesh* mesh, TransformNode* transform_node) : Mesh(material) {
		// Fills the VBO.
		geometry.num_vertices = mesh->mNumVertices;
		geometry.vbo = new Vertex[geometry.num_vertices];
		for (unsigned int i = 0; i < geometry.num_vertices; ++i) {
			geometry.vbo[i] = Vertex(
				Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z),	// Position
				Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),		// Normal
				Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)			// UV
			);
		}

		// Determines the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		geometry.num_indices = 0;
		for (unsigned int i = 0; i < num_faces; ++i) {
			geometry.num_indices += mesh->mFaces[i].mNumIndices;
		}

		// Fills the IBO.
		geometry.ibo = new GLuint[geometry.num_indices];
		for (unsigned int i = 0; i < num_faces; ++i) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
				geometry.ibo[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}

		this->transform_node = transform_node;
	}
}