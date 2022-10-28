#ifndef BD3GE_REGION_H
#define BD3GE_REGION_H

#include <algorithm>
#include <vector>

#include "../system/api.h"
#include "direction.h"
#include "vector.h"

namespace BD3GE {
	class BD3GE_API Region {
		public:
			static Region calculate_intersection(std::vector<Region> regions);
			static bool is_in_union(std::vector<Region> regions, BD3GE::Vector2 position);

			Region();
			Region(BD3GE::Vector2 position, BD3GE::Vector2 range);
			bool is_in_region(BD3GE::Vector2 position);
			std::vector<BD3GE::Vector2> get_bordering_positions();
			std::vector<BD3GE::Vector2> get_bordering_positions(std::vector<DIRECTION> directions);

		//private:
			Vector2 position;
			Vector2 range;
	};
}

#endif // BD3GE_REGION_H