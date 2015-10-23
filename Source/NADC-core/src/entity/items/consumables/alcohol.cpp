#include "alcohol.h"

// Gengine includes
#include "../equipment.h"

namespace glaze {
	namespace gengine {

		Alcohol::Alcohol(const std::string& name, const float& healthPoints, const float& alcohol) 
		: Consumable(name), _healthPoints(healthPoints), _alcohol(alcohol) { }

		void Alcohol::Interact(Player* player) {
			player->ChangeDrunkness(_alcohol / 100.0f);
			player->Heal(_healthPoints);

			player->getInventory()->Add(new Equipment("Empty bottle", 1, 0, Type::Hand));
			player->getInventory()->Destroy(this);
		}

	} // End namespace gengine
} // End namespace glaze