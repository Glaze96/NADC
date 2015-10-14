#pragma once
#include "item.h"

namespace glaze {
	namespace gengine {
		class LightSource : public Item {
		private: // Fields
			float _strength;
		
		public: // Constructors
			LightSource(const std::string& name, const float& strength);

		public: // getters
			const float& getStrength() const { return _strength; }

			Entity* clone() const override { return new LightSource(*this); }
			Entity* newClone() override {
				LightSource* e = new LightSource(*this);
				e->setId(getIdCounter());
				return e;
			}
		};

	} // End namespace gengine
} // End namespace glaze