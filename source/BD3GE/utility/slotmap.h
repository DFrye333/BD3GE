#ifndef BD3GE_SLOTMAP_H
#define BD3GE_SLOTMAP_H

#include <iostream>
#include <vector>

#include "../system/api.h"

namespace BD3GE {
	// The SlotmapKey allows for easy interface with the Slotmap, additionally providing built-in expiration for keys that have had their elements deleted.
	// The key consists of two elements:
	//	* Index: A value used by the Slotmap internally to address the desired datum.
	//	* Version: A value used to control the datum's lifetime, preventing duplicate deletion or access to an element that has recycled the desired element's storage.
	class SlotmapKey {
		public:
			SlotmapKey() {}
			SlotmapKey(unsigned short index, unsigned short version) : index(index), version(version) {}
			friend std::ostream& operator<<(std::ostream& out, const SlotmapKey& key) {
				return out << "(Index: " << key.index << ", Version: " << key.version << ")";
			}

			// Used by the Slotmap internally to address the desired datum.
			unsigned short index = 0;
			// Used to control the datum's lifetime, preventing duplicate deletion or access to an element that has recycled the desired element's storage.
			unsigned short version = 0;
	};

	// The Slotmap is a data structure that provides constant-time lookup, insertion, and removal, along with high-density/high-locality storage.
	// The goal is to free users from being concerned about the exact location of their data, without making them wish that they were!
	// Kudos to the following resources for teaching me about this neat data structure:
	//	* https://youtu.be/SHaAR7XPtNU
	//	* https://gamedev.stackexchange.com/a/33905/62203
	template<class T>
	class Slotmap {
		public:
			Slotmap() : Slotmap(0) {};

			// Initializes the Slotmap to accommodate for the given expected data quantity.
			Slotmap(unsigned short size) : size(size), free_head(0), free_tail(0) {
				resize(size);
			}

			SlotmapKey insert(T datum) {
				// The Slotmap has run out of storage space for new values and needs to resize.
				if (free_head == free_tail) {
					data_keys[free_head].index = size;
					resize(size * 2);
				}

				// Grabs the data key index of the on-deck free storage space.
				SlotmapKey& data_key = data_keys[free_head];

				// Determines where the next free storage space will be after the current insertion, either advancing through the data key indices sequentially or by following the index trail.
				unsigned short free_next = (data_key.version > 0 || (free_head + 1) >= size) ? data_key.index : free_head + 1;

				// Sets up the return user key.
				SlotmapKey map_key;
				// Updates the user key index to put at the on-deck free storage space, where the provided datum will be stored.
				map_key.index = free_head;
				// If the current data key's version is zero, it's a fresh space and needs its version initialized.
				if (data_key.version == 0) {
					++data_key.version;
				}
				// The user key version should reflect that of the data key.
				map_key.version = data_key.version;

				// Updates the location of the next free storage space.
				free_head = free_next;

				// Inserts the provided datum at end of the data collection and updates the data key's index to point at this end location.
				data.push_back(datum);
				data_key.index = data.size() - 1;

				// Adds an entry for the newly-added datum into the erase collection.
				erase.push_back(map_key.index);

				return map_key;
			};

			void remove(SlotmapKey map_key) {
				// Grabs the proper data key for the given user map key.
				SlotmapKey& data_key = data_keys[map_key.index];
				// If the user's map key version does not match that of the indicated index, or the provided user map key's version is zero, the key is expired or otherwise invalid.
				if (map_key.version != data_key.version || map_key.version == 0) { return; }

				// Increments the current data key's version in order to invalidate previous, existing generations of this key, indicating that they are no longer to be accepted as valid from the user.
				++data_key.version;

				// Performs a swap-and-pop on the outgoing datum, along with its corresponding erase entry. This allows data to be efficiently compacted.
				std::swap(data[data_key.index], data[data.size() - 1]);
				data.pop_back();
				std::swap(erase[data_key.index], erase[erase.size() - 1]);
				erase.pop_back();

				// Updates the index of the other datum (unrelated to that being deleted) that is moved by the deletion operation.
				// This is key part of the magic of the Slotmap data structure, and allows user-facing map keys to continue to be valid even when its underlying datum is relocated.
				data_keys[erase[data_key.index]].index = data_key.index;

				// Advances the free tail to consume the newly-vacated storage, leaving a breadcrumb behind to allow the free head to follow in its path.
				data_keys[free_tail].index = map_key.index;
				free_tail = map_key.index;
			};

			T* get(SlotmapKey map_key) {
				// Grabs the proper data key for the given user map key.
				SlotmapKey& data_key = data_keys[map_key.index];
				// If the user's map key version does not match that of the indicated index, the key is expired or otherwise invalid.
				if (map_key.version != data_key.version) { return nullptr; }

				// Returns the datum indicated by the provided user key.
				return &(data[data_key.index]);
			};

			T* operator[](SlotmapKey map_key) {
				return get(map_key);
			}

			void print() {
				std::cout << "Slotmap:" << "\n";
				std::cout << "----------" << "\n";

				// Prints the data key indirection layer.
				std::cout << "Data Keys: ";
				if (!data_keys.empty()) {
					for (SlotmapKey data_key : data_keys) {
						std::cout << " | ";
						std::cout << data_key.index << ", " << data_key.version;
					}
					std::cout << " |" << "\n";
				} else {
					std::cout << "[]" << "\n";
				}

				// Prints the actual user data.
				std::cout << "Data: ";
				if (!data.empty()) {
					for (T datum : data) {
						std::cout << " | ";
						std::cout << datum;
					}
					std::cout << " |" << "\n";
				}
				else {
					std::cout << "[]" << "\n";
				}

				// Prints the erase indices.
				std::cout << "Erase: ";
				if (!erase.empty()) {
					for (unsigned short erase_index : erase) {
						std::cout << " | ";
						std::cout << erase_index;
					}
					std::cout << " |" << "\n";
				}
				else {
					std::cout << "[]" << "\n";
				}

				std::cout << "Free Head: " << free_head << "\n";
				std::cout << "Free Tail: " << free_tail << "\n";
				std::cout << "Size: " << size << "\n";

				std::cout << "----------" << "\n";
				
				std::cout << std::endl;
			}

			void resize(unsigned short size) {
				// If an invalid size is provided, do not accept it.
				if (size <= 0) {
					size = 100;
				}

				// Updates the sizes of the underlying data structures and pulls the free tail to the new end of the storage.
				this->size = size;
				// Reserves memory for the data.
				data.reserve(size);
				erase.reserve(size);
				// Performs an actual resize, initializing the data keys.
				data_keys.resize(size);
				free_tail = size - 1;
			}

		private:
			// Points to the on-deck free storage space. When this coincides with the free tail, it's time to resize the Slotmap.
			unsigned short free_head;
			// Points to the last free storage space in the Slotmap.
			unsigned short free_tail;
			// Represents the quantity of data that the Slotmap is configured to store.
			unsigned short size;
			// Allows for data to be relocated as necessary without invalidating user handles.
			std::vector<unsigned short> erase;
			// Represents the indirection layer, freeing users from concerns about the exact location of their data.
			std::vector<SlotmapKey> data_keys;
			// Represents the actual user data.
			std::vector<T> data;
	};
}

#endif // BD3GE_SLOTMAP_H