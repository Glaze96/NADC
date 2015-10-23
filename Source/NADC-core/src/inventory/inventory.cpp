#include "inventory.h"

// System includes
#include <vector>

namespace glaze {
	namespace gengine {

		Inventory::Inventory(const int& maxSize) {
			_maxSize = maxSize;
		}

		Inventory::~Inventory() {
			for (unsigned int i = 0; i < _items.size(); i++) {
				delete _items[i];
			}
			_items.clear();
		}

		bool Inventory::Add(Entity* item, const bool& supressLog) {

			if (item == nullptr) {
				Log::AddMessage("Failed to add item to inventory");
				return false;
			}

			if (_items.size() >= _maxSize) {
				Log::AddMessage("Inventory is full");
				return false;
			}

			if (!supressLog) Log::AddMessage("Added '" + item->getName() + "' to inventory");

			_numItems++;
			item->setInInventory(true);
			_items.push_back(item);
			return true;
		}

		void Inventory::Destroy(Entity* entity) {

			for (unsigned int i = 0; i < _items.size(); i++) {
				if (_items.at(i)->getId() == entity->getId()) {
					_items.erase(_items.begin() + i);
					break;
				}
			}
			_numItems--;

			delete entity;
		}


	} // End namespace gengine
} // End namespace glaze