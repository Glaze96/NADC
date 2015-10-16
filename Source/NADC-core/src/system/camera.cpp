#include "camera.h"

// Glibrary includes
#include <Glibrary/maths/vector2.h>

namespace glaze {
using namespace glibrary;
	namespace gengine {

		Camera::Camera(const Vector2i& worldPosition, const Vector2i& screenPosition, const Vector2i& size) {
			_position = worldPosition;
			_screenPosition = screenPosition;
			_size = size;
		}

	} // End namespace gengine
} // End namespace glaze