#include "lightsource.h"

namespace glaze {
	namespace gengine {
		LightSource::LightSource(const std::string& name, const float& strength) 
		: Item(name) {
			_strength = strength;
			_itemType = Type::Hand;
		}
	}
}