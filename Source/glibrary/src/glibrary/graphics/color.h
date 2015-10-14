#pragma once
namespace glaze {
	namespace glibrary {

		class Color {
		public:
			static int RED;
			static int BLUE;
			static int GREEN;
			static int CYAN;
			static int MAGENTA;
			static int YELLOW;
			static int BLACK;
			static int WHITE;

		private:
			static int _numFills;

		private:
			Color() {}

		public:
			static void SetColor(const int& foreground, const int& background = BLACK);
			static void ResetColor();
			static void ResetCounter();
			static void Invert();
			static void ResetInvert();
			static void SetBold();
		};


	} // End namespace glibrary
} // End namespace glaze