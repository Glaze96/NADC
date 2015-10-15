#pragma once

// Gengine includes
#include "item.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class Equipment : public Item {
		protected: // Protected fields
			float _damage;
			float _armour;
			int _levelRequirement;

		public:
			Equipment(const std::string& name, const float& damage, const float& armour, const ItemType& itemType);
			~Equipment() { }

		public: // Public getters
			const float& getArmour() const { return _armour; }
			const float& getDamage() const { return _damage; }

		public:// Public methods
			void PrintStats(const Vector2i& position, unsigned int& lines) override;

			void Interact(Player* player) override;

			Entity* clone() const override { return new Equipment(*this); }
			Entity* newClone() override { 
				Equipment* e = new Equipment(*this);
				e->setId(getIdCounter());
				return e;
			}
		};

	} // End namespace gengine
} // End namespace glaze