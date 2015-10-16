#pragma once

// Glibrary includes
#include <Glibrary\maths\vector2.h>

// Gengine includes
#include "..\entity\creature\player.h"

namespace glaze {
	namespace gengine {

		class UIElement {

		protected:
			UIElement() {}

		protected:
			~UIElement() {}

			Vector2i _position;
			Vector2i _size;
						
		public: // Public getters
			Vector2i getSize() { return _size; }
			Vector2i getPosition() { return _position; }

		public: // Public methods
			virtual void Draw(Player* player) { }

		protected:
			void DrawBorders() const;

		};


	} // End namespace gengine
} // End namespace glaze