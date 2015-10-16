#include "color.h"

#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		int Color::_numFills = 0;
		int Color::RED = COLOR_RED;
		int Color::BLUE = COLOR_BLUE;
		int Color::GREEN = COLOR_GREEN;
		int Color::CYAN = COLOR_CYAN;
		int Color::MAGENTA = COLOR_MAGENTA;
		int Color::YELLOW = COLOR_YELLOW;
		int Color::BLACK = COLOR_BLACK;
		int Color::WHITE = COLOR_WHITE;

		void Color::SetColor(const int& foreground, const int& background) {
			_numFills++;
			init_pair(_numFills, foreground, background);
			attron(COLOR_PAIR(_numFills));
		}

		void Color::ResetColor() {
			attroff(COLOR_PAIR(_numFills));
		}

		void Color::ResetCounter() {
			_numFills = 0;
		}

		void Color::SetInvert() {
			attron(A_REVERSE);
		}

		void Color::ResetInvert() {
			attroff(A_REVERSE);
		}

		void Color::SetBold() {
			attron(A_BOLD);
		}

		void Color::ResetBold() {
			attroff(A_BOLD);
		}

	} // End namespace glibrary
} // End namespace glaze