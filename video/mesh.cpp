#include "mesh.h"

namespace BD3GE {
	Mesh::Mesh(Vector3 position, const aiMesh* mesh, aiTexture* texture, SimpleMaterial* simple_material, Vector3 scale) : Renderable(position) {
		// Fill the VBO.
		num_vertices = mesh->mNumVertices;
		vbo = new Vertex[num_vertices];
		for (unsigned int i = 0; i < num_vertices; ++i) {
			vbo[i] = Vertex(
				Vector3(mesh->mVertices[i].x * scale.v.g.x, mesh->mVertices[i].y * scale.v.g.y, mesh->mVertices[i].z * scale.v.g.z),	// Position
				Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z),													// Normal
				Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y)														// UV
			);
		}

		// Determines the total number of indices.
		const unsigned int num_faces = mesh->mNumFaces;
		num_indices = 0;
		for (unsigned int i = 0; i < num_faces; ++i) {
			num_indices += mesh->mFaces[i].mNumIndices;
		}

		// Fills the IBO.
		ibo = new GLuint[num_indices];
		for (unsigned int i = 0; i < num_faces; ++i) {
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; ++j) {
				ibo[(mesh->mFaces[i].mNumIndices * i) + j] = mesh->mFaces[i].mIndices[j];
			}
		}

		// TODO: Handle this allocation.
		this->materials.push_back(simple_material);

		setup();
	}
}