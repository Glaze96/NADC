#pragma once

// Gengine includes
#include "consumable.h"
#include "../../creature/player.h"
#include "../../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class Alcohol : public Consumable {
		private:
			float _healthPoints;
			float _alcohol;

		public:
			Alcohol(const std::string& name, const float& healthPoints, const float& alcohol);
			~Alcohol() { }

		public: // Public methods
			void Interact(Player* player) override;
			Entity* clone() const override { return new Alcohol(*this); }
			Entity* newClone() override {
				Alcohol* e = new Alcohol(*this);
				e->setId(getIdCounter());
				return e;
			}
		};



	} // End namespace gengine
} // End namespace glaze