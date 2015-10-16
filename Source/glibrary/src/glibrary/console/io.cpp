#include "io.h"

#include "cursor.h"
#include "..\..\curses\curses.h"

namespace glaze {
	namespace glibrary {

		/* ____In____ */

		std::string In::Readln() {
			echo();

			char str[80];

			getstr(str);

			noecho();

			return str;
		}

		std::string In::ReadlnAt(const int &x, const int &y) {
			Cursor::Move(x, y);

			std::string str = Readln();

			return str;
		}

		/* End ____In____ */


		/* ____Out____ */

		void Out::Printch(const char ch) {
			addch(ch);
		}

		void Out::PrintchAt(const int& x, const int& y, const char ch) {
			mvaddch(y, x, ch);
		}

		void Out::Println(std::string str, ...) {
			va_list args;

			va_start(args, str);
			vwprintw(stdscr, str.c_str(), args);
			va_end(args);
		}

		void Out::PrintlnAt(const int& x, const int& y, std::string str, ...) {
			Cursor::Move(x, y);

			va_list args;

			va_start(args, str);
			vwprintw(stdscr, str.c_str(), args);
			va_end(args);

		}
		/* End ____Out____ */

	}
}