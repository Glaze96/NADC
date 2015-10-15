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

		void UIManager::Init(const int& gameWindowWidth, const int& gameWindowHeight, const int& uiWidth) {
			
			int currentYPos = 0;
			
			InventoryUI* inventoryUI = new InventoryUI(
			Vector2i(gameWindowWidth, currentYPos),
			Vector2i(uiWidth/2, 40));
			_uiElements.push_back(inventoryUI);

			TileInfoUI* tileInfoUI = new TileInfoUI(
				Vector2i(gameWindowWidth + uiWidth / 2, currentYPos),
				Vector2i(uiWidth / 2 + 1, 40));
			_uiElements.push_back(tileInfoUI);

			currentYPos += _uiElements.back()->getSize().y;
			
			EntityInfoUI* entityInfoUI = new EntityInfoUI(
				Vector2i(gameWindowWidth, currentYPos),
				Vector2i(uiWidth, 30));
			_uiElements.push_back(entityInfoUI);
			
			currentYPos += _uiElements.back()->getSize().y;

			PlayerInfoUI* playerInfoUI = new PlayerInfoUI(
				Vector2i(gameWindowWidth, currentYPos),
				Vector2i(uiWidth / 2, gameWindowHeight - currentYPos));
			_uiElements.push_back(playerInfoUI);

			EquipmentUI* equipmentUI = new EquipmentUI(
				Vector2i(gameWindowWidth + uiWidth / 2, currentYPos),
				Vector2i(uiWidth / 2 + 1, gameWindowHeight - currentYPos));
			_uiElements.push_back(equipmentUI);

		}

		void UIManager::Draw(Player* player) {
			for (UIElement* uiElement : _uiElements)
				uiElement->Draw(player);
		}

	} // End namespace gengine
} // End namespace glaze