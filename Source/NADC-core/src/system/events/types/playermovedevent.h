#pragma once

#include <Glibrary/maths/vector2.h>

#include "../event.h"

namespace glaze {
	namespace gengine {
		class Player;
		
		class PlayerMovedEvent : public Event {
		public: // Public fields
			Player* _player;
			glibrary::Vector2i _fromPosition;
			glibrary::Vector2i _toPosition;

		public: // Con- & destructor's
			PlayerMovedEvent(Player* player, const glibrary::Vector2i& fromPosition, const glibrary::Vector2i& toPosition);
			~PlayerMovedEvent() {}
		};

	} // End namespace gengine
} // End namespace glaze