#include "shopkeeper.h"

// Glibrary includes
#include <Glibrary/console/io.h>
#include <Glibrary/maths/vector2.h>
#include <Glibrary/audio/soundmanager.h>

namespace glaze {
using namespace glibrary;
	namespace gengine {

		ShopKeeper::ShopKeeper(const std::string& name)
			: Creature(name, 'S') {
		}

		void ShopKeeper::PrintStats(const Vector2i& position, unsigned int& lines) {

			Creature::PrintStats(position, lines);
			lines += 2;

			Out::PrintlnAt(position.x + 2, position.y + lines, "Shopkeeper");

		}

		void ShopKeeper::Interact(Player* player) {
			SoundManager::GetPlayList("Hello")->PlayRandom(true);
		}


	} // End namespace gengine
} // End namespace glaze