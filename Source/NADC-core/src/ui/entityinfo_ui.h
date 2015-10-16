#pragma once

// Gengine includes
#include "uielement.h"

namespace glaze {
	using namespace glibrary;
	namespace gengine {

		class EntityInfoUI : public UIElement {
		public:
			virtual ~EntityInfoUI() {}

			EntityInfoUI(const Vector2i& position, const Vector2i& size);

		public:
			void Draw(Player* player) override;

		};


	} // End namespace gengine
} // End namespace glaze