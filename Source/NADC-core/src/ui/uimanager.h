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
			static void Init(const Camera& camera);
			static void Draw(Player* player);

		private: // Private methods
			static void CreateUIs(const Camera& camera);

		};


	} // End namespace gengine
} // End namespace glaze