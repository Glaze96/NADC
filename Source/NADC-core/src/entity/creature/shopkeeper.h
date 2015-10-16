#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "creature.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class ShopKeeper : public Creature {

		public: // Public con -& destructor's
			explicit ShopKeeper(const std::string& name);
			~ShopKeeper() { }

		public: // Public methods
			void PrintStats(const Vector2i& position, unsigned int& lines) override;
			void Interact(Player* player) override;
			Entity* clone() const override { return new ShopKeeper(*this); }
			Entity* newClone() override {
				ShopKeeper* e = new ShopKeeper(*this);
				e->setId(getIdCounter());
				return e;
			}
		};

	} // End namespace gengine
} // End namespace glaze