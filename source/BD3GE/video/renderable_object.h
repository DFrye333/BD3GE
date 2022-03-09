#ifndef BD3GE_RENDERABLE_OBJECT_H
#define BD3GE_RENDERABLE_OBJECT_H

#include "../system/api.h"
#include "../utility/object.h"
#include "../utility/vector.h"
#include "../video/renderable.h"

namespace BD3GE {
	class BD3GE_API RenderableObject : public Object {
		public:
			RenderableObject();
			RenderableObject(Vector3 position, Renderable* renderable);
			RenderableObject(Vector3 position, size_t renderable_id);
			RenderableObject(RenderableObject& other);
			~RenderableObject();
			RenderableObject& operator=(RenderableObject& other);

			Renderable* renderable;
			size_t renderable_id;
	};
}

#endif // BD3GE_RENDERABLE_OBJECT_H