#pragma once
#include <string>
#include <algorithm>

namespace glaze {
	namespace glibrary {

		inline bool CompareStrings(std::string first, std::string second, const bool& caseSensitive = true) {

			if (!caseSensitive) {
				transform(first.begin(), first.end(), first.begin(), ::tolower);
				transform(second.begin(), second.end(), second.begin(), ::tolower);
			}

			if (first == second)
				return true;
			
			return false;

		}

	}
}