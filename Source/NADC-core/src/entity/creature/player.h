#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "creature.h"
#include "../../inventory/inventory.h"
#include "../../entity/items/equipmentslot.h"

namespace glaze {
	namespace gengine {

		enum Menu {
			Inv,
			TileInfo
		};

		class Player : public Creature {
		private: // Private fields
			std::vector<EquipmentSlot> _equipmentSlots;
			Inventory _inventory;
			bool _moved;
			float _visibilityRange;
			float _drunkness;

			Menu _currentMenu;
			unsigned int _selection;

			bool _superVision;

		public: // Con -& destructors
			explicit Player(const std::string& name);
			void GenerateEquipmentSlots();
			~Player() {}

		public: // Public getters
			Inventory*							getInventory() { return &_inventory; }
			Menu								getMenu() const { return _currentMenu; }
			const unsigned int&					getSelection() const { return _selection; }
			const bool&							getMoved() const { return _moved; }
			const std::vector<EquipmentSlot>&	getEquipmentSlots() const { return _equipmentSlots; }
			const bool&							getSuperVision() const { return _superVision; }

		public: // Public setters
			void ChangeDrunkness(const float& value) { _drunkness < 0.0f ? _drunkness = 0.0f : _drunkness += value; }

		public: // Public methods
			void Update(const float& updateTick, const int& ch = 0);
			void Unequip(Item* item);
			void Equip(Item* item);
			void PrintStats(const Vector2i& position, unsigned int& lines) override;
			bool ToggleSuperVision();
			void UpdateVisibility() const;

		private: // Private methods
			void MakeAction(const Action& action);
			void Movement(const char& ch);
			void MenuInteraction(const int& ch);
			void UpdateEquipment();
			void Kill() override;
			void SelectionDown();
			void SelectionUp();

		};

	} // End namespace gengine
} // End namespace glaze