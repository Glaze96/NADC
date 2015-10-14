#pragma once

#include "../event.h"

namespace glaze {
	namespace gengine {
		class Player;

		class PlayerAttackedEvent : public Event {
		public: // Public fields
			Player* _player;

		public: // Public constructors
			PlayerAttackedEvent(Player* player);
		};

	} // End namespace gengine
} // End namespace glaze