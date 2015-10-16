#pragma once

// System includes
#include <string>

// Gengine includes
#include "../entity.h"
#include "../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class Stairs : public Entity {
		private:
			bool _up;

		public: // Public con -& destructor's-
			Stairs(const std::string& name, const char& appearance, const bool& up);
			~Stairs() { }

		public: // Public methods
			void DoAction(Entity* entity, Player* player, const Action& action) override;
			Entity* clone() const override { return new Stairs(*this); }
			Entity* newClone() override {
				Stairs* e = new Stairs(*this);
				e->setId(getIdCounter());
				return e;
			}
			

		};

	} // End namespace gengine
} // End namespace glaze