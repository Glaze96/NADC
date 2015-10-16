#include "equipment.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "../creature/player.h"

namespace glaze {
	//using namespace glibrary;
	namespace gengine {

		Equipment::Equipment(const std::string& name, const float& damage, const float& armour, const Type& itemType)
			: Item(name, itemType), _damage(damage), _armour(armour), _levelRequirement(0) {
		}

		void Equipment::PrintStats(const Vector2i&  position, unsigned int& lines) {

			Item::PrintStats(position, lines);

			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Equipment");

			if (_damage > 0.0f) {
				lines++;
				Color::SetColor(Color::RED);
				Out::PrintlnAt(position.x + 2, position.y + lines, "Damage: %.1f", _damage);
				Color::ResetColor();
			}

			if (_armour > 0.0f) {
				lines++;
				Color::SetColor(Color::YELLOW);
				Out::PrintlnAt(position.x + 2, position.y + lines, "Armour: %.1f", _armour);
				Color::ResetColor();
			}

			lines++;

			Out::PrintlnAt(position.x + 2, position.y + lines, "LevelRequirement: %i", _levelRequirement);
			Color::ResetColor();
		}

		void Equipment::Interact(Player* player) {
			if (getEquipped()) {
				player->Unequip(this);
			}
			else {
				player->Equip(this);
			}
		}

	} // End namespace gengine
} // End namespace glaze