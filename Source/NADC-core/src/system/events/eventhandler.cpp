#include "eventhandler.h"

#include <Glibrary/console/log.h>

#include "eventlistener.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		typedef std::pair<EventListener*, std::vector<Event::Type>> listenerPair;
		
		void EventHandler::Subscribe(EventListener* listener, std::vector<Event::Type> types) {
			_listeners.insert(_listeners.end(), listenerPair(listener, types));
		}

		void EventHandler::UnSubscribe(EventListener* listener) {
			_listeners.erase(listener);
			Log::AddMessage("Someone stopped listening!");
		}

		void EventHandler::Dispatch(Event& event) const {

			for (auto& listener : _listeners) {
				
				for (const auto& eventType : listener.second) {
					
					if (event.getHandled())
						return;

					if (eventType == event.getType())
						event.setHandled(listener.first->onEvent(event));

				}


			}

		}

	} // End namespace gengine
} // End namespace glaze