#include "uielement.h"

// Glibrary includes
#include <Glibrary/graphics/draw.h>

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		void UIElement::DrawBorders() const {
			DrawBox(Boxf((float)_size.x, (float)_size.y, (float)_position.x, (float)_position.y));
		}


	} // End namespace gengine
} // End namespace glaze