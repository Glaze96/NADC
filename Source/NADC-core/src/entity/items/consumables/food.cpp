#include "food.h"

// Gengine includes
#include "../../creature/player.h"

namespace glaze {
	namespace gengine {

		Food::Food(const std::string& name, const float& healthPoints)
			: Consumable(name) {
			_healthPoints = healthPoints;
		}

		void Food::Interact(Player* player) {
			player->Heal(_healthPoints);
			player->getInventory()->Destroy(this);
		}


	} // End namespace gengine
} // End namespace glaze