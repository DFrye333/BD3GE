#include "renderable.h"

namespace BD3GE {
	RenderableUnit::RenderableUnit() : material(nullptr), transform_node(nullptr) {}

	RenderableUnit::RenderableUnit(Material* material) : material(material), transform_node(nullptr) {}

	RenderableUnit::RenderableUnit(Material* material, TransformNode* transform_node) : material(material), transform_node(transform_node) {}

	RenderableUnit::RenderableUnit(const RenderableUnit& other) : RenderableUnit() {
		*this = other;
	}

	RenderableUnit::~RenderableUnit() {
		delete[] geometry.vbo;
		geometry.vbo = nullptr;

		delete[] geometry.ibo;
		geometry.ibo = nullptr;

		delete material;
		material = nullptr;

		delete transform_node;
		transform_node = nullptr;
	}

	const RenderableUnit& RenderableUnit::operator=(const RenderableUnit& other) {
		this->geometry.vao_handle = other.geometry.vao_handle;
		this->geometry.num_vertices = other.geometry.num_vertices;
		this->geometry.num_indices = other.geometry.num_indices;

		if (other.geometry.vbo) {
			delete this->geometry.vbo;
			this->geometry.vbo = new Vertex[sizeof(other.geometry.vbo)];
			*(this->geometry.vbo) = *(other.geometry.vbo);
		}
		if (other.geometry.ibo) {
			delete this->geometry.ibo;
			this->geometry.ibo = new unsigned int[sizeof(other.geometry.ibo)];
			*(this->geometry.ibo) = *(other.geometry.ibo);
		}
		if (other.material) {
			delete this->material;
			this->material = other.material->clone();
		}
		if (other.transform_node) {
			delete this->transform_node;
			this->transform_node = new TransformNode;
			this->transform_node->parent = other.transform_node->parent;
			this->transform_node->transform = other.transform_node->transform;
		}

		return *this;
	}
}