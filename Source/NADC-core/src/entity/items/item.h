#pragma once

// System includes
#include <string>

// Gengine includes
#include "../entity.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		enum ItemType {
			Error,
			Hand,
			Head,
			Neck,
			Torso,
			Hands,
			Legs,
			Feet,
			Consumable,
			Key
		};

		class Item : public Entity {
		protected:
			ItemType _itemType;

		public: 
			explicit Item(const std::string& name, const ItemType& itemType = ItemType::Error);
			~Item() { }

		public: // Public getters
			const ItemType& getItemType() const { return _itemType; }

		public: // Public methods
			std::string GetItemTypeName() const;
			void DoAction(Entity* entity, Player* player, const Action& action) override;
			Entity* clone() const override { return new Item(*this); }
			Entity* newClone() override {
				Item* e = new Item(*this);
				e->setId(getIdCounter());
				return e;
			}

		protected: // Protected methods
			void PickUp(Player* player);
			void Drop(Player* player);
			void Equip(Player* player);
			void UnEquip(Player* player);
			void PrintStats(const Vector2i& position, unsigned int& lines) override;
		};

	} // End namespace gengine
} // End namespace glaze