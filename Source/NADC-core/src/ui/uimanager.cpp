#include "uimanager.h"

// System includes
#include <vector>

// Gengine includes
#include "inventory_ui.h"
#include "playerinfo_ui.h"
#include "equipment_ui.h"
#include "tileinfo_ui.h"
#include "entityinfo_ui.h"
#include "..\system\camera.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		std::vector<UIElement*> UIManager::_uiElements;

		void UIManager::Init(const Camera& camera) {
			CreateUIs(camera);
		}

		void UIManager::CreateUIs(const Camera& camera) {

			InventoryUI* inventoryUI = new InventoryUI(
				Vector2i(camera.getSize().x, 0),
				Vector2i(51, 40));

			PlayerInfoUI* playerInfoUI = new PlayerInfoUI(
				Vector2i(camera.getSize().x, inventoryUI->getSize().y),
				Vector2i(25, 20));

			EquipmentUI* equipmentUI = new EquipmentUI(
				Vector2i(camera.getSize().x + playerInfoUI->getSize().x, inventoryUI->getSize().y),
				Vector2i(inventoryUI->getSize().x - playerInfoUI->getSize().x, playerInfoUI->getSize().y));

			TileInfoUI* tileInfoUI = new TileInfoUI(
				Vector2i(camera.getSize().x, inventoryUI->getSize().y + playerInfoUI->getSize().y),
				Vector2i(inventoryUI->getSize().x, 20));

			EntityInfoUI* entityInfoUI = new EntityInfoUI(
				Vector2i(camera.getSize().x, inventoryUI->getSize().y + playerInfoUI->getSize().y + tileInfoUI->getSize().y),
				Vector2i(inventoryUI->getSize().x, camera.getSize().y - (inventoryUI->getSize().y + playerInfoUI->getSize().y + tileInfoUI->getSize().y)));

			_uiElements.push_back(inventoryUI);
			_uiElements.push_back(playerInfoUI);
			_uiElements.push_back(equipmentUI);
			_uiElements.push_back(tileInfoUI);
			_uiElements.push_back(entityInfoUI);

		}

		void UIManager::Draw(Player* player) {
			for (UIElement* uiElement : _uiElements)
				uiElement->Draw(player);
		}

	} // End namespace gengine
} // End namespace glaze