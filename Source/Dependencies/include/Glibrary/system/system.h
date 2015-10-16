#ifndef SYSTEM_CLASS
#define SYSTEM_CLASS

namespace glaze {
	namespace glibrary {

		/* ____System____ */

		class System {
		public:
			static void ClearStdWin();
			static void InitStdWin();
			static void EndStdWin();
			static void RefreshStdWin();

		};

	} // End namespace glibrary
} // End namespace glaze

#endif