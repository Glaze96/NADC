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
			: Creature(name, 'P', Color::WHITE, 100.0f), _inventory(Inventory(34)), _currentMenu(Menu::Inv), _selection(0), _xray(false) {
			setVisible(true);

			GenerateEquipmentSlots();

			_inventory.Add(EntityTemplate::Find("Bronze sword"));
			_inventory.Add(EntityTemplate::Find("helmet"));
		}

		void Player::GenerateEquipmentSlots() {
			_equipmentSlots.push_back(EquipmentSlot("Right hand",	Item::Type::Hand));
			_equipmentSlots.push_back(EquipmentSlot("Left hand",	Item::Type::Hand));
			_equipmentSlots.push_back(EquipmentSlot("Head",			Item::Type::Head));
			_equipmentSlots.push_back(EquipmentSlot("Neck",			Item::Type::Neck));
			_equipmentSlots.push_back(EquipmentSlot("Torso",		Item::Type::Torso));
			_equipmentSlots.push_back(EquipmentSlot("Hands",		Item::Type::Hands));
			_equipmentSlots.push_back(EquipmentSlot("Legs",			Item::Type::Legs));
			_equipmentSlots.push_back(EquipmentSlot("Feet",			Item::Type::Feet));
		}

		void Player::DispatchPlayerMovedEvent(const Vector2i& direction) {
			PlayerMovedEvent event = PlayerMovedEvent(this, getPosition(), getPosition() + direction);
			_level->getEventHandler().Dispatch(event);
		}

		void Player::SelectionDown() {

			_selection++;

			if (_currentMenu == Menu::Inv) {
				if (_selection > _inventory.getNumItems() - 1)
					_selection = 0;
			}
			else {
				if (_selection > _level->GetNumEntitiesAtPosition(getPosition()) - 1)
					_selection = 0;
			}
		}

		void Player::SelectionUp() {

			if (_selection == 0) {

				if (_currentMenu == Menu::Inv)
					_selection = _inventory.getNumItems() - 1;
				else
					_selection = _level->GetNumEntitiesAtPosition(getPosition()) - 1;

			}
			else {
				_selection--;
			}
		}

		void Player::Update(const float& updateTick, const int& ch) {

			Movement(ch);

			MenuInteraction(ch);


		}

		void Player::Equip(Item* item) {

			Item::Type type = item->getItemType();

			for (auto& eqSlot : _equipmentSlots) {
				if (type == eqSlot.getItemType()) {

					if (eqSlot.getFull())
						eqSlot.UnEquip();

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

		bool Player::ToggleXray() {
			if (_xray)
				_xray = false;
			else
				_xray = true;

			Log::AddMessage(_xray ? "Xray on" : "Xray off");

			return _xray;
		}

		void Player::MakeAction(const Action& action) {

			if (_currentMenu == Menu::Inv) {

				std::vector<Entity*> items = _inventory.getItems();

				if (_selection < items.size()) {
					Entity* item = items.at(_selection);
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
			float resolution = 0.2f;
#else
			float resolution = 0.075f;
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

			bool moved = false;

			Vector2i direction;

			if (ch == 'w') {
				direction = Vector2i(0, -1);
				moved = true;
			}
			else if (ch == 'a') {
				direction = Vector2i(-1, 0);
				moved = true;
			}
			else if (ch == 's') {
				direction = Vector2i(0, 1);
				moved = true;
			}
			else if (ch == 'd') {
				direction = Vector2i(1, 0);
				moved = true;
			}

			if (rand() % 100 / 100.0f < _drunkness && moved) {
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

			if (moved) {
				Move(direction);
				DispatchPlayerMovedEvent(direction);
				UpdateVisibility();
				ChangeDrunkness(-0.002f);
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

			if (ch == '2') {
				_selection = 0;
				_currentMenu = Menu::Inv;
			}
			else if (ch == '1') {
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

		bool Player::ToggleGodmode() {
			if (!_godmode) {
				_godmode = true;
				_invincible = true;
				_xray = true;
			}
			else {
				_godmode = false;
				_invincible = false;
				_xray = false;
			}

			Log::AddMessage(_godmode ? "Godmode on" : "Godmode off");

			return _godmode;
		}

		void Player::PrintStats(const Vector2i& position, unsigned int& lines) {

			Creature::PrintStats(position, lines);

			lines += 2;

			Out::PrintlnAt(position.x + 2, position.y + lines, "Player");

			if (_drunkness > 0.0f) {
				lines++;
				Out::PrintlnAt(position.x + 2, position.y + lines, "Drunkenness: %.1f%%", _drunkness * 100);
			}

		}

		void Player::Kill() {
			Log::AddMessage("Oh noes, you died!");
		}

	} // End namespace gengine
} // End namespace glaze