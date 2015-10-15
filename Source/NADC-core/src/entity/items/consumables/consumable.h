#pragma once

// Gengine includes
#include "../item.h"
#include "../../../system/events/eventhandler.h"

namespace glaze {
	namespace gengine {

		class Consumable : public Item {
		protected:
			explicit Consumable(const std::string& name);
			~Consumable() { }
			
		public:// Public methods
			void PrintStats(const Vector2i& position, unsigned int& lines) override;
			Entity* clone() const override { return new Consumable(*this); }
			Entity* newClone() override { 
				Consumable* e = new Consumable(*this);
				e->setId(getIdCounter());
				return e;
			}

		};



	} // End namespace gengine
} // End namespace glaze