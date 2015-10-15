#pragma once

// Gengine includes
#include "equipment.h"
#include "equipmentslot.h"

namespace glaze {
	namespace gengine {

		EquipmentSlot::EquipmentSlot(const std::string& name, const ItemType& type) {
			_name = name;
			_itemType = type;
			_full = false;
			_item = nullptr;
		}

		std::string EquipmentSlot::GetNameAndItem() const {
			
			if (_full)
				return _name + ": " + _item->getName();
			else
				return _name + ": -";
		}

		void EquipmentSlot::UnEquip() {
			if (_item != nullptr)
				_item->setEquipped(false);
			_item = nullptr;
			_full = false;
		}

		void EquipmentSlot::Equip(Item* item) { 
			_item = item;
			_full = true;
		}

	} // End namespace gengine
} // End namespace glaze