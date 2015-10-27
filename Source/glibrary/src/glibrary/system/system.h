#ifndef SYSTEM_CLASS
#define SYSTEM_CLASS

namespace glaze {
	namespace glibrary {

		/* ____System____ */

		class System {
		public:
			static void Init(const int& windowWidth = 80, const int& windowHeight = 25, const bool& noEcho = false, const bool& disableCursor = false, const bool& pauseForInput = true);
			static void ClearStdWin();
			static void InitStdWin();
			static void EndStdWin();
			static void RefreshStdWin();

		};

	} // End namespace glibrary
} // End namespace glaze

#endif