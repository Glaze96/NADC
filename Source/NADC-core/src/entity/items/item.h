#pragma once

// System includes
#include <string>

// Gengine includes
#include "../entity.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {



		class Item : public Entity {
		public:
			enum Type {
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

		protected:
			Type _itemType;

		public: 
			explicit Item(const std::string& name, const Type& itemType = Error);
			~Item() { }

		public: // Public getters
			const Type& getItemType() const { return _itemType; }

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