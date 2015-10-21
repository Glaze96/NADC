#pragma once
#include <string>
#include <algorithm>

namespace glaze {
	namespace glibrary {

		inline void RemoveSpaces(std::string& str) {
			bool done = false;

			while (!done) {

				int spacePos = str.find_first_of(' ');

				if (spacePos != -1) {
					str.erase(spacePos, 1);
				}
				else {
					done = true;
				}


			}
		}

		inline bool CompareStrings(std::string first, std::string second, const bool& caseSensitive = true) {

			if (!caseSensitive) {
				transform(first.begin(), first.end(), first.begin(), ::tolower);
				transform(second.begin(), second.end(), second.begin(), ::tolower);
			}

			if (first == second)
				return true;

			return false;

		}

		inline bool IsInteger(const char& ch) {

			if (ch < 48 || ch > 57)
				return false;

			return true;
		}

		inline bool IsInteger(const std::string& str) {

			int numInts = 0;

			for (int i = 0; i < str.size(); i++) {
				if (IsInteger(str.at(i)))
					numInts++;
			}

			if (numInts == str.size())
				return true;

			return false;
		}

		inline bool ContainsInteger(const std::string& str) {

			for (int i = 0; i < str.size(); i++) {
				if (IsInteger(str.at(i)))
					return true;
			}

			return false;

		}

	}
}