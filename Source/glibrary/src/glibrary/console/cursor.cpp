#include "cursor.h"

#include "window.h"
#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		int Cursor::LastXPosition = 0;
		int Cursor::LastYPosition = 0;

		void Cursor::Move(const int &x, const int &y) {

			LastXPosition = stdscr->_curx;
			LastYPosition = stdscr->_cury;

			move(y, x);
		}

		void Cursor::Move(const Window &window, const int &x, const int &y) {
			Move(window.getWindow(), x, y);
		}

		void Cursor::Move(WINDOW *window, const int &x, const int &y) {
			LastXPosition = window->_curx;
			LastYPosition = window->_cury;

			wmove(window, y, x);
		}

	} // End namespace glibrary
} // End namespace glaze