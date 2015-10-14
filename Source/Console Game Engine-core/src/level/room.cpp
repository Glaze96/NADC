#include "room.h"

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "level.h"

namespace glaze {
	namespace gengine {

		Room::Room(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void Room::PushTilesToLevel(Level* level) const {
			for (int y = 0; y < _size.y; y++) {
				for (int x = 0; x < _size.x; x++) {
					level->SetTile(_position.x + x, _position.y + y, Tile('.', Tile::Type::Floor));
				}
			}

		}

	} // End namespace gengine
} // End namespace glaze