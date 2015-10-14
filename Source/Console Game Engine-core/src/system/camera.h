#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		class Camera {
		private:
			Vector2i _position;
			Vector2i _screenPosition;
			Vector2i _size;

		public: // Public con -& destructors
			Camera() {}
			Camera(const Vector2i& worldPosition, const Vector2i& screenPosition, const Vector2i& size);
			~Camera() {}

		public: // Public getters
			Vector2i getPosition() const { return _position; }
			Vector2i getSize() const { return _size; }
			Vector2i getScreenPosition() const { return _screenPosition; }

		};

	} // End namespace gengine
} // End namespace glaze