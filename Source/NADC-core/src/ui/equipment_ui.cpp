#include "equipment_ui.h"

// Glibrary includes
#include <Glibrary/console/io.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		EquipmentUI::EquipmentUI(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void EquipmentUI::Draw(Player* player) {

			unsigned int lines = 2;

			Out::PrintlnAt(_position.x + 2, _position.y + lines, "Equipment");

			lines += 2;

			for (auto& equipment : player->getEquipmentSlots()) {
				Out::PrintlnAt(_position.x + 2, _position.y + lines, "%s", equipment.GetNameAndItem().c_str());
				lines++;
			}

			DrawBorders();
		}

	} // End namespace gengine
} // End namespace glaze