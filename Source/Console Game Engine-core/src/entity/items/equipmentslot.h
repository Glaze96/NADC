#pragma once

// System includes
#include <string>

// Gengine includes
#include "item.h"

namespace glaze {
	namespace gengine {

		class EquipmentSlot  {
		private: // Private fields
			std::string _name;
			Item* _item;
			ItemType _itemType;
			bool _full;

		public:
			EquipmentSlot(const std::string& name, const ItemType& type);
		
		public: // Public getters
			Item* getItem() const { return _item; }
			ItemType getItemType() const { return _itemType; }
			bool getFull() const { return _full; }

		public: // Public Getters
			std::string GetNameAndItem() const;

		public: // Public methods
			void UnEquip();
			void Equip(Item* item);
		};


	} // End namespace gengine
} // End namespace glaze