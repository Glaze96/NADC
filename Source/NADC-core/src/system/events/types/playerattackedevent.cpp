#include "playerattackedevent.h"

namespace glaze {
	namespace gengine {


		PlayerAttackedEvent::PlayerAttackedEvent(Player* player) 
			: Event(Event::Type::PlayerAttacked) , _player(player) {}

	} // End namespace gengine
} // End namespace glaze