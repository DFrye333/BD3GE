#ifndef BD3GE_COMPONENT_MANAGER_H
#define BD3GE_COMPONENT_MANAGER_H

#include "../system/api.h"
#include "../utility/slotmap.h"
#include "../utility/transform.h"
#include "../video/renderable.h"
#include "../video/light.h"

namespace BD3GE {
	extern "C" class BD3GE_API ComponentManager {
		public:
			static SlotmapKey add_transform(Transform transform);
			static SlotmapKey add_renderable(Renderable renderable);
			static SlotmapKey add_directional_light(DirectionalLight directional_light);
			static SlotmapKey add_point_light(PointLight point_light);
			static SlotmapKey add_spot_light(SpotLight spot_light);
			static Transform* get_transform(SlotmapKey transform_key);
			static Renderable* get_renderable(SlotmapKey renderable_key);
			static DirectionalLight* get_directional_light(SlotmapKey directional_light_key);
			static PointLight* get_point_light(SlotmapKey point_light_key);
			static SpotLight* get_spot_light(SlotmapKey spot_light_key);
			static void remove_transform(SlotmapKey transform_key);
			static void remove_renderable(SlotmapKey renderable_key);
			static void remove_directional_light(SlotmapKey light_key);
			static void remove_point_light(SlotmapKey light_key);
			static void remove_spot_light(SlotmapKey light_key);
			static void clear_all();

		private:
			static Slotmap<Transform> transforms;
			static Slotmap<Renderable> renderables;
			static Slotmap<DirectionalLight> directional_lights;
			static Slotmap<PointLight> point_lights;
			static Slotmap<SpotLight> spot_lights;
	};
}

#endif // BD3GE_COMPONENT_MANAGER_H