#ifndef BD3GE_MODEL_H
#define BD3GE_MODEL_H

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../management/shader_manager.h"
#include "../system/globals.h"
#include "../utility/log.h"
#include "../utility/transform.h"
#include "../video/mesh.h"
#include "../video/renderable.h"

namespace BD3GE {
	class Model : public Renderable {
		public:
			Model();
			Model(std::string model_file_path);
			void load_model(std::string model_file_path);
			void process_tree(const aiScene* scene, aiNode* node, TransformNode* parent_transform_node);
	};
}

#endif // BD3GE_MODEL_H