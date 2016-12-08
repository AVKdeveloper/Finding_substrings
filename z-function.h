// This header includes class SubstringFinder, which works with total string (pattern + unique symbol + string).
// Nevertheless, we store only z-function for first pattern.size() symbols of total string.

#ifndef Z_FUNCTION_H
#define Z_FUNCTION_H

#include <vector>
#include <string>
#include <algorithm>
#include <deque>

class SubstringFinder {
	std::string pattern_;
	std::vector<int> z_function_; // z_function for first pattern.size() symbols
	int left_; // [left, right] is rightmost segment, which is similar to some prefix  
	int right_;
public:
	SubstringFinder(const std::string& pattern);
	void InitializeZFunction();
	int AnalyseNewStringSymbol(const std::deque<char>& following_string_symbols, int index_in_string);
};

#endif // Z_FUNCTION_H