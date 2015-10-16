#include "tile.h"
#include <Glibrary/graphics/color.h>

namespace glaze {
using namespace glibrary;
	namespace gengine {

		Tile::Tile(const char& appearance, const Tile::Type& type)
		: _appearance(appearance), _type(type), _visible(false) { }


	} // End namespace gengine
} // End namespace glaze