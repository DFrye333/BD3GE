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
			Object(const Object& other);
			Object(Object&& other);
			~Object();
			Transform* get_world_transform() const;
			Renderable* get_renderable() const;
			SlotmapKey get_world_transform_key() const;
			SlotmapKey get_renderable_key() const;
			void set_world_transform(Transform&& world_transform);
			void set_renderable(Renderable&& renderable);
			void set_world_transform(SlotmapKey world_transform_key);
			void set_renderable(SlotmapKey renderable_key);
			void set_position(const Vector3 position);
			void set_orientation(const Vector3 orientation);
			void set_scale(Vector3 scaler);
			void translate(Vector3 translation);
			void rotate(Vector3 angle);
			Vector3 get_position();
			Vector3 get_forward();
			Vector3 get_left();
			Vector3 get_up();
			const Object& operator=(const Object& other);
			const Object& operator=(Object&& other);

		protected:
			void cleanup();
			void cleanup_transform();
			void cleanup_renderable();

			SlotmapKey world_transform;
			SlotmapKey renderable;
			bool owns_transform;
			bool owns_renderable;
	};
}

#endif // BD3GE_OBJECT_H