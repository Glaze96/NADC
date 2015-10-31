#pragma once

namespace glaze {
	namespace glibrary {

		class System {
		public:
			static void Init(const int& windowWidth = 80, const int& windowHeight = 25, const bool& noEcho = false, const bool& disableCursor = false, const bool& pauseForInput = true);
			static void ClearStdWin();
			static void EndStdWin();
			static void RefreshStdWin();

		};

	} // End namespace glibrary
} // End namespace glaze
