#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "level.h"

namespace glaze {
	namespace gengine {

		class Room {
		private:
			Vector2i _position;
			Vector2i _size;

		public: // Public con -& destructors
			Room(const Vector2i& position, const Vector2i& size);
			~Room() { }

		public: // Public getters
			Vector2i getPosition() const { return _position; }
			Vector2i getSize() const { return _size; }

		public: // Public methods
			void PushTilesToLevel(Level *level) const;

		};

	} // End namespace gengine
} // End namespace glaze