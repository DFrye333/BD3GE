#ifndef BD3GE_COMPONENT_MANAGER_H
#define BD3GE_COMPONENT_MANAGER_H

#include "../system/api.h"
#include "../utility/slotmap.h"
#include "../utility/transform.h"
#include "../video/renderable.h"

namespace BD3GE {
	extern "C" class BD3GE_API ComponentManager {
		public:
			static SlotmapKey add_transform(Transform transform);
			static SlotmapKey add_renderable(Renderable renderable);
			static Transform* get_transform(SlotmapKey transform_key);
			static Renderable* get_renderable(SlotmapKey renderable_key);
			static void clear_all();

		private:
			static Slotmap<Transform> transforms;
			static Slotmap<Renderable> renderables;
	};
}

#endif // BD3GE_COMPONENT_MANAGER_H