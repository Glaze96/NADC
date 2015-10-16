#pragma once
#include "event.h"
#include <vector>

namespace glaze {
	namespace gengine {
		
		class EventListener {
		protected:
			EventListener() {}
			virtual ~EventListener() {}

			virtual bool onEvent(Event& event) = 0;
			friend class EventHandler;
		};

	} // End namespace gengine
} // End namespace glaze