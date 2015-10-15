#pragma once
namespace glaze {
	namespace glibrary {

		class Color {
		public: // Public fields
			static int RED;
			static int BLUE;
			static int GREEN;
			static int CYAN;
			static int MAGENTA;
			static int YELLOW;
			static int BLACK;
			static int WHITE;

		private: // Private fields
			static int _numFills;

		private:
			Color() {}
			~Color() {}

		public: // Public methods
			static void SetColor(const int& foreground, const int& background = BLACK);
			static void ResetColor();
			static void ResetCounter();
			static void SetInvert();
			static void ResetInvert();
			static void SetBold();
			static void ResetBold();
		};


	} // End namespace glibrary
} // End namespace glaze