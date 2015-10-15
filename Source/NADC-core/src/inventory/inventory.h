#pragma once

// System includes
#include <vector>

// Gengine includes
#include "../entity/items/item.h"

namespace glaze {
	namespace gengine {

		class Inventory {
		private:
			std::vector<Entity*> _items;
			unsigned int _maxSize;

		public: // Public con -& destructors
			explicit Inventory(const int& maxSize);
			~Inventory();

		public: // Public getters
			unsigned int getMaxSize() const { return _maxSize; }
			std::vector<Entity*>* getItems() { return &_items; }

		public: // Public methods
			bool AddEntity(Entity* item, const bool& supressLog = false);
			void Destroy(Entity* entity);

		};


	} // End namespace gengine
} // End namespace glaze