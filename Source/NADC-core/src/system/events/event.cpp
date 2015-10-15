#include "event.h"

namespace glaze {
	namespace gengine {

		Event::Event(const Type& type) 
		: _type(type), _handled(false) { }

	} // End namespace gengine
} // End namespace glaze