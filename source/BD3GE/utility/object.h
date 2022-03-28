#ifndef BD3GE_OBJECT_H
#define BD3GE_OBJECT_H

#include "../system/api.h"
#include "../management/component_manager.h"
#include "../utility/slotmap.h"
#include "../utility/transform.h"
#include "../utility/vector.h"

namespace BD3GE {
	extern "C" class BD3GE_API Object {
		public:
			Object();
			Transform* get_world_transform();
			Renderable* get_renderable();
			void set_world_transform(Transform world_transform);
			void set_renderable(Renderable renderable);
			void set_position(Vector3 position);
			void set_orientation(Vector3 orientation);
			void set_scale(Vector3 scaler);
			void translate(Vector3 translation);
			void rotate(Vector3 angle);
			Vector3 get_position();
			Transform& get_transform();

			SlotmapKey world_transform;
			SlotmapKey renderable;
	};
}

#endif // BD3GE_OBJECT_H