#include "system.h"

#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		/* ____System_____ */

		void System::ClearStdWin() {
			clear();
		}
		
		void System::InitStdWin() {
			initscr();
		}

		void System::EndStdWin() {
			endwin();
		}

		void System::RefreshStdWin() {
			refresh();
		}

		/* End ____System____ */

	} // End namespace glibraty
} // End namespace glaze
