#include "model.h"

namespace BD3GE {
	Model::Model() {}

	Model::Model(std::string model_file_path) {
		load_model(model_file_path);
	}

	void Model::load_model(std::string model_file_path) {
		// Import asset residing at given file path.
		unsigned int importer_options =
			aiProcess_CalcTangentSpace |
			aiProcess_JoinIdenticalVertices |
			aiProcess_Triangulate |
			aiProcess_SortByPType |
			aiProcess_FlipWindingOrder |
			aiProcess_FlipUVs;

		Assimp::Importer model_importer;
		const aiScene* scene = model_importer.ReadFile(model_file_path, importer_options);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			g_log->write(Log::TYPE::ERR, "Model load failure at '" + model_file_path + "': " + model_importer.GetErrorString());
			return;
		}

		g_log->write(Log::TYPE::INFO, "Model loading success: " + model_file_path);
		g_log->write(Log::TYPE::INFO, "Loading mesh with:");
		g_log->write(Log::TYPE::INFO, "\tVertices: " + std::to_string(scene->mMeshes[0]->mNumVertices));
		g_log->write(Log::TYPE::INFO, "\tFaces: " + std::to_string(scene->mMeshes[0]->mNumFaces));
		g_log->write(Log::TYPE::INFO, "\tMaterials: " + std::to_string(scene->mNumMaterials));
		g_log->write(Log::TYPE::INFO, "\tTextures: " + std::to_string(scene->mNumTextures));

		process_tree(scene, scene->mRootNode, nullptr);
	}

	void Model::process_tree(const aiScene* scene, aiNode* node, TransformNode* parent_transform_node) {
		size_t shader_id = ShaderManager::get_shader_id(ShaderManifest("light.vert", "light.frag"));

		aiMatrix4x4t transform_matrix = node->mTransformation;
		TransformNode* transform_node = new TransformNode;
		transform_node->parent = parent_transform_node;
		transform_node->transform = Transform(Matrix4(
			transform_matrix.a1, transform_matrix.a2, transform_matrix.a3, transform_matrix.a4,
			transform_matrix.b1, transform_matrix.b2, transform_matrix.b3, transform_matrix.b4,
			transform_matrix.c1, transform_matrix.c2, transform_matrix.c3, transform_matrix.c4,
			transform_matrix.d1, transform_matrix.d2, transform_matrix.d3, transform_matrix.d4
		));
		for (unsigned short i = 0; i < node->mNumMeshes; ++i) {
			Mesh* current_mesh = new Mesh(
				new MappedMaterial(shader_id, scene->mMaterials[scene->mMeshes[node->mMeshes[i]]->mMaterialIndex]),
				scene->mMeshes[node->mMeshes[i]],
				transform_node
			);
			renderable_units.push_back(current_mesh);
		}

		for (unsigned short i = 0; i < node->mNumChildren; ++i) {
			process_tree(scene, node->mChildren[i], transform_node);
		}
	}
}