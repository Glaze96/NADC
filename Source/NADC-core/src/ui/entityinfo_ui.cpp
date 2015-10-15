#include "entityinfo_ui.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		EntityInfoUI::EntityInfoUI(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void EntityInfoUI::Draw(Player* player) {

			unsigned int lines = 0;

			Menu currentMenu = player->getMenu();
			unsigned int selection = player->getSelection();

			if (currentMenu == Menu::Inv) {

				std::vector<Entity*>* entities = player->getInventory()->getItems();

				if (selection < entities->size()) {
					Entity* entity = entities->at(selection);
					entity->PrintStats(_position, lines);
				}

			}
			else if (currentMenu == Menu::TileInfo) {

				std::vector<Entity*> entities = player->getLevel()->GetEntitiesAtPosition(player->getPosition());

				if (selection < entities.size()) {
					Entity* entity = entities.at(selection);
					entity->PrintStats(_position, lines);
				}
			}

			DrawBorders();
		}

	} // End namespace gengine
} // End namespace glaze