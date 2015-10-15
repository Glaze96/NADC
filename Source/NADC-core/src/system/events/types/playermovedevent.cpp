#include "playermovedevent.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {
				
		PlayerMovedEvent::PlayerMovedEvent(Player* player, const Vector2i& fromPosition, const Vector2i& toPosition)
			: Event(Event::Type::PlayerMoved), _player(player), _fromPosition(fromPosition), _toPosition(toPosition) { }

	} // End namespace gengine
} // End namespace glaze