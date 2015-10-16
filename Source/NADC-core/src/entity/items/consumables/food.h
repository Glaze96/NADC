#pragma once

// Gengine includes
#include "consumable.h"

namespace glaze {
	namespace gengine {

		class Food : public Consumable {
		private:
			float _healthPoints;

		public:
			Food(const std::string& name, const float& healthPoints);
			~Food() { }

		public:
			void Interact(Player* player) override;

			Entity* clone() const override { return new Food(*this); }
			Entity* newClone() override {
				Food* e = new Food(*this);
				e->setId(getIdCounter());
				return e;
			}
		};

	} // End namespace gengine
} // End namespace glaze