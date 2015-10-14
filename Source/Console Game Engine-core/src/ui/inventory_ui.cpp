#include "inventory_ui.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		InventoryUI::InventoryUI(const Vector2i& position, const Vector2i& size) {
			_position = position;
			_size = size;
		}

		void InventoryUI::Draw(Player* player) {

			Menu menu = player->getMenu();
			unsigned int selection = player->getSelection();
			Inventory* inventory = player->getInventory();

			unsigned int lines = 2;

			Out::PrintlnAt(_position.x + 2, lines, "Inventory");
			lines += 2;

			std::vector<Entity*>* items = inventory->getItems();

			for (unsigned int i = 0; i < inventory->getMaxSize() - items->size(); i++) {

				bool selected = false;

				if (menu == Menu::Inv && selection == i + items->size())
					selected = true;

				if (selected)
					Color::Invert();

				Out::PrintlnAt(_position.x + 2, lines + i + items->size(), "--------------------------------------");

				if (selected)
					Color::ResetInvert();

			}

			for (unsigned int i = 0; i < items->size(); i++) {
				bool selected = false;

				if (menu == Menu::Inv && selection == i)
					selected = true;

				Entity* currentItem = items->at(i);

				if (selected)
					Color::Invert();

				Out::PrintlnAt(_position.x + 2, lines + i, "%s%s", currentItem->getEquipped() ? "*" : "", currentItem->getName().c_str());

				if (selected)
					Color::ResetInvert();
			}

			DrawBorders();
		}


	} // End namespace gengine
} // End namespace glaze