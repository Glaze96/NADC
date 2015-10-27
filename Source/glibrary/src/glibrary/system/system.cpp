#include "system.h"

#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		/* ____System_____ */

		void System::Init(const int& windowWidth, const int& windowHeight, const bool& noEcho, const bool& disableCursor, const bool& pauseForInput) {


			initscr(); // Initializes pdcurses
			cbreak();
			keypad(stdscr, 1);		// Enables function keys
			start_color();			// Enables colors


			resize_term(windowHeight, windowWidth); // Resize to specified height and width

			if (noEcho)
				noecho();				// Do not echo input

			if (disableCursor)
				curs_set(false);		// Disables cursor

			if (!pauseForInput)
				nodelay(stdscr, true);	// Do not pause for input
		}

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
