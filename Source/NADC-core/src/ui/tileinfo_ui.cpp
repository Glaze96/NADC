#include "tileinfo_ui.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "../entity/creature/player.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		TileInfoUI::TileInfoUI(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void TileInfoUI::Draw(Player* player) {

			unsigned int selection = player->getSelection();
			Menu menu = player->getMenu();

			unsigned int lines = 2;

			Out::PrintlnAt(_position.x + 2, _position.y + lines, "Ground:");

			lines += 2;

			std::vector<Entity*> entities(player->getLevel()->GetEntitiesAtPosition(player->getPosition()));

			if (entities.size() < _size.y - lines - 2) {
				for (unsigned int i = 0; i < _size.y - lines - entities.size() - 2; i++) {

					bool selected = false;

					if (menu == Menu::TileInfo && selection == i + entities.size())
						selected = true;

					if (selected)
						Color::SetInvert();

					Out::PrintlnAt(_position.x + 2, _position.y + lines + i + entities.size(), "--------------------------------------");

					if (selected)
						Color::ResetInvert();

				}
			}

			
			for (unsigned int i = 0; i < entities.size(); i++) {
				if (i > (unsigned int)(_size.y - 7))
					break;

				bool selected = false;

				if (menu == Menu::TileInfo && selection == i)
					selected = true;

				if (selected) 
					Color::SetInvert();				

				Out::PrintlnAt(_position.x + 2, _position.y + lines, entities.at(i)->getName().c_str());

				if (selected)
					Color::ResetInvert();

				lines++;
			}


			DrawBorders();
		}

	} // End namespace gengine
} // End namespace glaze