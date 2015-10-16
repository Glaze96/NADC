#include "consumable.h"

// Glibrary includes
#include <Glibrary/console/io.h>

// Gengine includes
#include "../../creature/player.h"

namespace glaze {
	//using namespace glibrary;
	namespace gengine {
		
		Consumable::Consumable(const std::string& name)
			: Item(name) {
			_itemType = Type::Consumable;
		}

		void Consumable::PrintStats(const Vector2i&  position, unsigned int& lines) {

			Item::PrintStats(position, lines);
			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Consumable");
			lines++;

		}

	} // End namespace gengine
} // End namespace glaze