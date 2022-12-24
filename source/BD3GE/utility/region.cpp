#include "region.h"

namespace BD3GE {
	Region Region::calculate_intersection(std::vector<Region> regions) {
		if (regions.empty()) {
			return Region();
		} else if (regions.size() < 2) {
			return regions[0];
		}

		Region intersection = regions[0];
		for (unsigned short i = 1; i < regions.size(); ++i) {
			Region current_region = regions[i];

			Region left_region, right_region;
			if (current_region.position.v.g.x < intersection.position.v.g.x) {
				left_region = current_region;
				right_region = intersection;
			} else {
				left_region = intersection;
				right_region = current_region;
			}

			Region top_region, bottom_region;
			if (current_region.position.v.g.y < intersection.position.v.g.y) {
				top_region = intersection;
				bottom_region = current_region;
			} else {
				top_region = current_region;
				bottom_region = intersection;
			}

			short left_region_right_edge = (left_region.position + left_region.range).v.g.x;
			short right_region_left_edge = right_region.position.v.g.x;
			short bottom_region_top_edge = (bottom_region.position + bottom_region.range).v.g.y;
			short top_region_bottom_edge = top_region.position.v.g.y;

			// No overlap between the current candidate region and the running cumulative intersection means no overall intersection.
			if (left_region_right_edge < right_region_left_edge || bottom_region_top_edge < top_region_bottom_edge) {
				return Region();
			}

			BD3GE::Vector2 new_intersection_lower_endpoint = BD3GE::Vector2(right_region_left_edge, top_region_bottom_edge);

			short right_region_right_edge = (right_region.position + right_region.range).v.g.x;
			short top_region_top_edge = (top_region.position + top_region.range).v.g.y;
			BD3GE::Vector2 new_intersection_upper_endpoint(
				std::min(right_region_right_edge, left_region_right_edge),
				std::min(top_region_top_edge, bottom_region_top_edge)
			);

			intersection = Region(new_intersection_lower_endpoint, new_intersection_upper_endpoint - new_intersection_lower_endpoint);
		}

		return intersection;
	}

	bool Region::is_in_union(std::vector<Region> regions, BD3GE::Vector2 position) {
		for (Region region : regions) {
			if (region.is_in_region(position)) {
				return true;
			}
		}

		return false;
	}

	Region::Region() : position(BD3GE::Vector2(0, 0)), range(BD3GE::Vector2(0, 0)) {}

	Region::Region(BD3GE::Vector2 position, BD3GE::Vector2 range) : position(position), range(range) {}

	bool Region::is_in_region(BD3GE::Vector2 position) {
		return (
			(position.v.g.x >= this->position.v.g.x) && (position.v.g.x < (this->position.v.g.x + this->range.v.g.x)) &&
			(position.v.g.y >= this->position.v.g.y) && (position.v.g.y < (this->position.v.g.y + this->range.v.g.y))
		);
	}

	std::vector<BD3GE::Vector2> Region::get_bordering_positions() {
		return get_bordering_positions(std::vector<DIRECTION>{ DIRECTION::NORTH, DIRECTION::EAST, DIRECTION::SOUTH, DIRECTION::WEST });
	}

	std::vector<BD3GE::Vector2> Region::get_bordering_positions(std::vector<DIRECTION> directions) {
		unsigned char direction_mask = 0;
		for (DIRECTION direction : directions) {
			switch (direction) {
				case DIRECTION::NORTH: direction_mask |= 1; break;
				case DIRECTION::EAST: direction_mask |= 2; break;
				case DIRECTION::SOUTH: direction_mask |= 4; break;
				case DIRECTION::WEST: direction_mask |= 8; break;
			}
		}

		std::vector<BD3GE::Vector2> bordering_positions;
		if (direction_mask & 1 || direction_mask & 4) {
			for (unsigned short x = 1; x < (position.v.g.x + range.v.g.x) - 1; ++x) {
				if (direction_mask & 4) bordering_positions.emplace_back(BD3GE::Vector2(x, position.v.g.y));
				if (direction_mask & 1) bordering_positions.emplace_back(BD3GE::Vector2(x, position.v.g.y + range.v.g.y - 1));
			}
		}
		if (direction_mask & 2 || direction_mask & 8) {
			for (unsigned short y = 1; y < (position.v.g.y + range.v.g.y) - 1; ++y) {
				if (direction_mask & 8) bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x, y));
				if (direction_mask & 2) bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x + range.v.g.x - 1, y));
			}
		}

		if (direction_mask & 4 || direction_mask & 8) {
			bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x, position.v.g.y));
		}
		if (direction_mask & 8 || direction_mask & 1) {
			bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x, position.v.g.y + range.v.g.y - 1));
		}
		if (direction_mask & 1 || direction_mask & 2) {
			bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x + range.v.g.x - 1, position.v.g.y + range.v.g.y - 1));
		}
		if (direction_mask & 2 || direction_mask & 4) {
			bordering_positions.emplace_back(BD3GE::Vector2(position.v.g.x + range.v.g.x - 1, position.v.g.y));
		}

		return bordering_positions;
	}
}