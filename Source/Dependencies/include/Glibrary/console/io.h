#pragma once

#include <string>

namespace glaze {
	namespace glibrary {

		class Out {
		public:
			static void Printch(const char ch);
			static void PrintchAt(const int &x, const int &y, const char ch);
			
			static void Println(std::string str, ...);
			static void PrintlnAt(const int& x, const int& y, std::string str, ...);

		};

		class In {
		public:
			static std::string Readln();
			static std::string ReadlnAt(const int &x, const int &y);
		};
	}
}