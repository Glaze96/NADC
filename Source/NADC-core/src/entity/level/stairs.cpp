#include "stairs.h"

// Gengine includes
#include "../../level/levelmanager.h"
#include <Glibrary/graphics/color.h>

namespace glaze {
	namespace gengine {

		Stairs::Stairs(const std::string& name, const char& appearance, const bool& up) 
		: Entity(name, appearance, Color::MAGENTA), _up(up) { }

		void Stairs::DoAction(Entity* entity, Player* player, const Action& action) {
			
			if (_up)
				LevelManager::GoUp(player->getXray());
			else
				LevelManager::GoDown(player->getXray());

		}

	} // End namespace gengine
} // End namespace glaze