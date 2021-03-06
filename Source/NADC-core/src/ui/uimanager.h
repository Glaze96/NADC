#pragma once

// System includes
#include <vector>

// Gengine includes
#include "uielement.h"
#include "../system/camera.h"

namespace glaze {
	namespace gengine {

		class UIManager {
		private: // Private fields
			static std::vector<UIElement*> _uiElements;
		private:
			UIManager() { }
			~UIManager() { }

		public: // Public methods
			static void Init(const int& gameWindowWidth, const int& gameWindowHeight, const int& uiWidth);
			static void Draw(Player* player);

		};

	} // End namespace gengine
} // End namespace glaze