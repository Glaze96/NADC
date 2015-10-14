#pragma once
#include <string>

namespace glaze {
	namespace glibrary {

		inline bool CompareStrings(std::string first, std::string second, const bool& caseSensitive = true) {

			if (!caseSensitive) {
				std::transform(first.begin(), first.end(), first.begin(), ::tolower);
				std::transform(second.begin(), second.end(), second.begin(), ::tolower);
			}

			if (first == second)
				return true;
			
			return false;

		}

	}
}