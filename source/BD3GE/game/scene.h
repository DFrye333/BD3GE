#ifndef BD3GE_SCENE_H
#define BD3GE_SCENE_H

#include <cmath>
#include <cstdlib>
#include <utility>
#include <vector>

#include "../system/api.h"
#include "../utility/color.h"
#include "../utility/object.h"
#include "../utility/slotmap.h"
#include "../video/brush.h"
#include "../video/camera.h"
#include "../video/mesh.h"
#include "../video/model.h"
#include "../video/renderable.h"
#include "../video/shader.h"

namespace BD3GE {
	extern "C" class SceneNode {
		public:
			SceneNode();
			SceneNode(SlotmapKey parent, Object object);
			SceneNode(const SceneNode& other);
			const SceneNode& operator=(const SceneNode& other);

			SlotmapKey parent;
			Object object;
	};

	extern "C" class BD3GE_API Scene {
		public:
			Scene();
			~Scene();
			SlotmapKey add_object(Object new_node);
			SlotmapKey add_object(Object new_node, SlotmapKey parent_node);
			SlotmapKey add_renderable_object(Object new_node);
			SlotmapKey add_renderable_object(Object new_node, SlotmapKey parent_node);
			Object* get_object(SlotmapKey node_key);
			void remove_object(SlotmapKey node_key);

			Camera* camera;
			SlotmapKey root_scene_node;
			Slotmap<SceneNode> scene_nodes;
			std::vector<SlotmapKey> renderable_objects;
			std::vector<Light*> lights;
			std::vector<Material*> lit_materials;
	};
}

#endif // BD3GE_SCENE_H