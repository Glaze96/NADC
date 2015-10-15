#include "playerinfo_ui.h"

// Glibrary includes
#include <Glibrary/console/io.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		PlayerInfoUI::PlayerInfoUI(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void PlayerInfoUI::Draw(Player* player) {

			unsigned int lines = 2;

			Out::PrintlnAt(_position.x + 2, _position.y + lines, "Player Info");
			
			player->PrintStats(_position, lines);

			DrawBorders();
		}

	} // End namespace gengine
} // End namespace glaze