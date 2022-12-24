#include "quadtree.h"

namespace BD3GE {
	QuadtreeData::QuadtreeData(SlotmapKey key, Vector2 position) : key(key), position(position) {}

	Quadtree::Quadtree() : region(Region(Vector2(-1000, -1000), Vector2(2000, 2000))) {}

	Quadtree::Quadtree(Region region) : region(region) {}

	Quadtree::Quadtree(Region region, std::vector<QuadtreeData>& nodes) : region(region) {
		for (QuadtreeData node : nodes) {
			this->insert(node);
		}
	}

	void Quadtree::insert(QuadtreeData node) {
		// If the current level is full, fragment and shift the children downward.
		if (this->nodes.size() + 1 > max_nodes_per_level) {
			children[0] = new Quadtree(Region(region.position, region.range / 2));
			children[1] = new Quadtree(Region(Vector2(region.position.v.g.x + region.range.v.g.x / 2, region.position.v.g.y), region.range / 2));
			children[2] = new Quadtree(Region(Vector2(region.position.v.g.x, region.position.v.g.y + region.range.v.g.y / 2), region.range / 2));
			children[3] = new Quadtree(Region(Vector2(region.position.v.g.x + region.range.v.g.x / 2, region.position.v.g.y + region.range.v.g.y / 2), region.range / 2));

			for (QuadtreeData& existing_node : this->nodes) {
				for (unsigned short i = 0; i < 4; ++i) {
					if (children[i]->region.is_in_region(existing_node.position)) {
						children[i]->insert(existing_node);
						break;
					}
				}
			}
			this->nodes.clear();
		}
		
		// Insert the new node either in the appropriate child level, or on the current level if there are no children levels.
		if (this->has_children()) {
			for (unsigned short i = 0; i < 4; ++i) {
				if (children[i]->region.is_in_region(node.position)) {
					children[i]->insert(node);
					break;
				}
			}
		} else {
			this->nodes.emplace_back(node);
		}
	}

	void Quadtree::remove(QuadtreeData node) {
		if (!this->has_children()) {
			for (unsigned short i = 0; i < this->nodes.size(); ++i) {
				if (this->nodes[i].key == node.key) {
					this->nodes.erase(this->nodes.begin() + i);
				}
			}
		} else {
			for (unsigned short i = 0; i < 4; ++i) {
				if (this->children[i]->region.is_in_region(node.position)) {
					return this->children[i]->remove(node);
				}
			}
		}
	}

	std::vector<SlotmapKey> Quadtree::collect_overlapping_nodes(Region region) {
		std::vector<SlotmapKey> overlapping_nodes;

		Region intersection = Region::calculate_intersection(std::vector<Region>{ this->region, region });
		if (intersection.calculate_area() == 0.0f) {
			return std::vector<SlotmapKey>();
		}

		if (this->has_children()) {
			for (unsigned short i = 0; i < 4; ++i) {
				std::vector<SlotmapKey> child_overlapping_nodes = children[i]->collect_overlapping_nodes(region);
				overlapping_nodes.insert(overlapping_nodes.end(), child_overlapping_nodes.begin(), child_overlapping_nodes.end());
			}
		} else {
			for (QuadtreeData& node : this->nodes) {
				overlapping_nodes.emplace_back(node.key);
			}
		}

		return overlapping_nodes;
	}

	bool Quadtree::has_children() {
		return children[0] != nullptr;
	}

	void Quadtree::print() {
		if (!this->has_children()) {
			std::cout << "Region: " << this->region << " | Nodes: " << this->nodes.size() << std::endl;

			return;
		}

		for (unsigned short i = 0; i < 4; ++i) {
			children[i]->print();
		}
	}
}