#ifndef BD3GE_QUADTREE_H
#define BD3GE_QUADTREE_H

#include <vector>

#include "../system/api.h"
#include "region.h"
#include "slotmap.h"
#include "vector.h"

namespace BD3GE {
	class BD3GE_API QuadtreeData {
		public:
			QuadtreeData(SlotmapKey key, Vector2 position);

			SlotmapKey key;
			Vector2 position;
	};

	class BD3GE_API Quadtree {
		public:
											Quadtree();
											Quadtree(Region region);
											Quadtree(Region region, std::vector<QuadtreeData>& nodes);
			void							insert(QuadtreeData node);
			void							remove(QuadtreeData node);
			unsigned int					size();
			unsigned int					size(Region region);
			std::vector<SlotmapKey>			collect_overlapping_nodes(Region region);
			bool							has_children();
			void							print();

			Region region;
			std::vector<QuadtreeData> nodes;
			Quadtree* children[4] = { nullptr };
			unsigned short max_nodes_per_level = 10;
	};
}

#endif // BD3GE_QUADTREE_H