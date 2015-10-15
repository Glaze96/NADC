#pragma once

#include <vector>
#include <map>

#include "event.h"

namespace glaze {
	namespace gengine {
		class EventListener;
		
		class EventHandler {
		private:
			std::map<EventListener*, std::vector<Event::Type>> _listeners;
			
		public:
			void Dispatch(Event& event) const;
			void Subscribe(EventListener* listener, std::vector<Event::Type> types);
			void UnSubscribe(EventListener* listener);
		};

	} // End namespace gengine
} // End namespace glaze