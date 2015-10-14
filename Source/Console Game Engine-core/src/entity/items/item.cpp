#include "item.h"

// Glibrary includes
#include <Glibrary/maths/vector2.h>
#include <Glibrary/console/io.h>
#include <Glibrary/graphics/color.h>

// Gengine includes
#include "../creature/player.h"

namespace glaze {
	namespace gengine {

		Item::Item(const std::string& name, const ItemType& itemType)
			: Entity(name, 'I', Color::YELLOW), _itemType(itemType) { }

		void Item::DoAction(Entity* entity, Player* player, const Action& action) {
			
			if (getInInventory()) {

				if (getEquipped()) {

					if (action == Action::Right) {
						//TODO: add usage of item, for example bows
					}
					else {
						entity->Interact(player);
					}

				}
				else {

					if (action == Action::Right) {
						entity->Interact(player);
					}
					else {
						Drop(player);
					}

				}

			}
			else {
				PickUp(player);
			}

		}

		void Item::PickUp(Player* player) {

			setLevel(player->getLevel());

			// Copy item
			Entity* copyOfItem = clone();

			// Add to inventory
			if (player->getInventory()->AddEntity(copyOfItem)) {
				// Destroy item in level, if successfully addded to inventory
				_level->DestroyEntity(this);
			}
		}

		void Item::Drop(Player* player) {

			_level = player->getLevel();

			// Unequip item if equipped
			if (getEquipped()) { player->Unequip(this); }

			// Copy item
			Entity* copyOfItem = clone();

			// Move it to player position
			copyOfItem->setPosition(player->getPosition());

			// Add that item to level
			if (_level->AddEntity(copyOfItem, player->getPosition())) {
				// Destroy item in inventory, if successfully added to level
				player->getInventory()->Destroy(this);
			}
		}

		void Item::Equip(Player* player) {
			player->Equip(this);
		}
		void Item::UnEquip(Player* player) {
			player->Unequip(this);
		}

		void Item::PrintStats(const Vector2i& position, unsigned int& lines) {

			Entity::PrintStats(position, lines);

			lines += 2;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Item");

			lines++;
			Out::PrintlnAt(position.x + 2, position.y + lines, "Type: %s", GetItemTypeName().c_str());


		}

		std::string Item::GetItemTypeName() const {

			switch (_itemType) {

			case ItemType::Hand:
			{
				return "Hand";
			}
			case ItemType::Head:
			{
				return "Head";
			}
			case ItemType::Neck:
			{
				return "Neck";
			}
			case ItemType::Torso:
			{
				return "Torso";
			}
			case ItemType::Legs:
			{
				return "Legs";
			}
			case ItemType::Hands:
			{
				return "Hands";
			}
			case ItemType::Feet:
			{
				return "Feet";
			}
			case ItemType::Consumable:
			{
				return "Consumable";
			}
			case ItemType::Key:
			{
				return "Key";
			}
			default: {
				return "ASFDDFG%G¤G";
			}
			}
		}


	} // End namespace gengine
} // End namespace glaze