#pragma once

// System includes
#include <string>

// Gengine includes
#include "../entity/creature/player.h"

namespace glaze {
	namespace gengine {
		class Console {
		public:
			static void Input(Player* player);
			static void RunCommand(const std::string& command, Player* player);
		};

	}
}