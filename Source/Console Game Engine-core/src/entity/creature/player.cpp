#include "player.h"

// Glibrary includes
#include <Glibrary/maths/vector2.h>
#include <Glibrary/console/io.h>
#include <Glibrary/maths/geometry.h>
#include <Curses/curses.h>

// Gengine includes
#include "../items/equipment.h"
#include "../entitytemplate.h"
#include <Glibrary/graphics/color.h>
#include "../items/lightsource.h"
#include "../../system/events/types/playermovedevent.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		Player::Player(const std::string&  name)
			: Creature(name, 'P', Color::WHITE, 100.0f), _inventory(Inventory(34)), _moved(false), _currentMenu(Menu::Inv), _selection(0), _superVision(false) {
			setVisible(true);

			GenerateEquipmentSlots();

			_inventory.AddEntity(EntityTemplate::Find("sword"));
			_inventory.AddEntity(EntityTemplate::Find("helmet"));
		}

		void Player::GenerateEquipmentSlots() {
			_equipmentSlots.push_back(EquipmentSlot("Right hand", ItemType::Hand));
			_equipmentSlots.push_back(EquipmentSlot("Left hand", ItemType::Hand));
			_equipmentSlots.push_back(EquipmentSlot("Head", ItemType::Head));
			_equipmentSlots.push_back(EquipmentSlot("Neck", ItemType::Neck));
			_equipmentSlots.push_back(EquipmentSlot("Torso", ItemType::Torso));
			_equipmentSlots.push_back(EquipmentSlot("Hands", ItemType::Hands));
			_equipmentSlots.push_back(EquipmentSlot("Legs", ItemType::Legs));
			_equipmentSlots.push_back(EquipmentSlot("Feet", ItemType::Feet));
		}

		void Player::SelectionDown() {

			_selection++;

			if (_currentMenu == Menu::Inv) {
				if (_selection > _inventory.getMaxSize() - 1)
					_selection = 0;
			}
			else {
				if (_selection > 13) //TODO: fix hardcode
					_selection = 0;
			}
		}

		void Player::SelectionUp() {

			if (_selection == 0) {
				if (_currentMenu == Menu::Inv)
					_selection = _inventory.getMaxSize() - 1;
				else
					_selection = 13; //TODO: fix hardcode
			}
			else {
				_selection--;
			}
		}

		void Player::Update(const float& updateTick, const int& ch) {

			Movement(ch);

			MenuInteraction(ch);

			ChangeDrunkness(-updateTick / 800.0f);

		}

		void Player::Equip(Item* item) {

			ItemType type = item->getItemType();

			for (auto& eqSlot : _equipmentSlots) {
				if (type == eqSlot.getItemType()) {

					if (eqSlot.getFull()) {
						eqSlot.UnEquip();
					}

					eqSlot.Equip(item);
					item->setEquipped(true);
					UpdateEquipment();
					return;
				}
			}

			Log::AddMessage("Was unable to equip item '" + item->getName() + "'", Message::Type::Warning);

		}

		void Player::Unequip(Item* item) {

			for (auto& eqSlot : _equipmentSlots) {
				if (eqSlot.getItem() != nullptr) {
					if (eqSlot.getItem()->getId() == item->getId()) {

						eqSlot.UnEquip();
						UpdateEquipment();
						return;
					}
				}
			}

			Log::AddMessage("Was unable to unequip item '" + item->getName() + "'", Message::Type::Warning);

		}

		bool Player::ToggleSuperVision() {
			if (_superVision)
				_superVision = false;
			else
				_superVision = true;

			Log::AddMessage("Supervision " + std::to_string(_superVision));

			return _superVision;
		}

		void Player::MakeAction(const Action& action) {

			_moved = true;

			if (_currentMenu == Menu::Inv) {

				std::vector<Entity*>* items = _inventory.getItems();

				if (_selection < items->size()) {
					Entity* item = items->at(_selection);
					item->DoAction(item, this, action);
				}

			}
			else if (_currentMenu == Menu::TileInfo) {

				std::vector<Entity*> entities = _level->GetEntitiesAtPosition(getPosition());

				if (_selection < entities.size()) {
					Entity* entity = entities.at(_selection);
					entity->DoAction(entity, this, action);
				}
			}

		}

		void Player::UpdateVisibility() const {

#ifdef _DEBUG
			float resolution = 0.3f;
#else
			float resolution = 0.1f;
#endif


			for (float angle = 0.0f; angle < 360.0f; angle += resolution) {
				Ray ray(Vector2f(getPosition() + 0.5f), Vector2f::AngleToVector(angle));

				for (float pos = 0.0f; pos < 20.0f; pos += 1.0f) {

					Vector2i position(ray.Position + (ray.Direction * pos));

					const Tile currentTile(_level->GetTile(position));
					
					_level->SetTileVisible(position);
					if (currentTile.getType() == Tile::Type::Wall) {
						break;
					}


				}

			}
		}

		void Player::Movement(const char& ch) {

			_moved = false;
			bool move = false;

			Vector2i direction;

			if (ch == 'w') {
				direction = Vector2i(0, -1);
				move = true;
			}
			else if (ch == 'a') {
				direction = Vector2i(-1, 0);
				move = true;
			}
			else if (ch == 's') {
				direction = Vector2i(0, 1);
				move = true;
			}
			else if (ch == 'd') {
				direction = Vector2i(1, 0);
				move = true;
			}

			if ((rand() % 1000) / 1000.0f < _drunkness && move) {
				switch (rand() % 4) {
				case 0:
					direction = Vector2i(-1, 0);
					break;
				case 1:
					direction = Vector2i(1, 0);
					break;
				case 2:
					direction = Vector2i(0, -1);
					break;
				case 3:
					direction = Vector2i(0, 1);
					break;
				}
			}

			if (move) {
				PlayerMovedEvent e = PlayerMovedEvent(this, getPosition(), getPosition() + direction);
				_level->getEventHandler().Dispatch(e);
				_moved = Move(direction);
				UpdateVisibility();
			}

		}

		void Player::MenuInteraction(const int& ch) {

			if (ch == KEY_LEFT ||
				ch == 'j') {
				MakeAction(Action::Left);
			}

			if (ch == KEY_RIGHT ||
				ch == 'l') {
				MakeAction(Action::Right);
			}

			if (ch == '1') {
				_selection = 0;
				_currentMenu = Menu::Inv;
			}
			else if (ch == '2') {
				_selection = 0;
				_currentMenu = Menu::TileInfo;
			}

			if (ch == KEY_UP ||
				ch == 'i') {
				SelectionUp();
			}

			if (ch == KEY_DOWN ||
				ch == 'k') {
				SelectionDown();

			}
		}

		void Player::UpdateEquipment() {

			_totalArmour = 0.0f;
			_totalDamage = 0.0f;
			_visibilityRange = 0.0f;
			for (auto& eqSlot : _equipmentSlots) {
				Item* item = eqSlot.getItem();
				if (item != nullptr) {
					_totalDamage += ((Equipment*)item)->getDamage();
					_totalArmour += ((Equipment*)item)->getArmour();
					_visibilityRange += ((LightSource*)item)->getStrength();
				}
			}

		}

		void Player::PrintStats(const Vector2i& position, unsigned int& lines) {

			Creature::PrintStats(position, lines);

			lines += 2;

			Out::PrintlnAt(position.x + 2, position.y + lines, "Player");

			if (_drunkness > 0.0f) {
				lines++;
				Out::PrintlnAt(position.x + 2, position.y + lines, "Drunkness: %.1f%%", _drunkness * 100);
			}

		}

		void Player::Kill() {
			Log::AddMessage("Oh noes, you died!");
		}

	} // End namespace gengine
} // End namespace glaze