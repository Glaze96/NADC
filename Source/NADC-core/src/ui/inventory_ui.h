#pragma once

// Glibrary includes
#include <Glibrary/maths/vector2.h>

// Gengine includes
#include "uielement.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		class InventoryUI : public UIElement {
		public:
			virtual ~InventoryUI() {}

			InventoryUI(const Vector2i& position, const Vector2i& size);

		public:
			void Draw(Player* player) override;
			
		};


	} // End namespace gengine
} // End namespace glaze