// This program finds positions of substrings in string using z-function
// We find z-function for total string (pattern + unique symbol + string)
// Memory O(pattern.size());   Time O(total_string.size());

#include <fstream>
#include <string>
#include <deque>
#include "z-function.h"

int main()
{
	std::fstream file_in;
	file_in.open("input.txt", std::fstream::in);
	std::string pattern;
	file_in >> pattern;
	SubstringFinder finder(pattern);
	finder.InitializeZFunction(); // count z-function for pattern
	// in any moment we may need up to the following pattern.size() symbols of string
	std::deque<char> following_string_synbols;
	char symbol; // next symbol from input
	for (int i = 0; i < pattern.size() && file_in >> symbol; ++i) {
		following_string_synbols.push_back(symbol);
	}

	std::fstream file_out;
	file_out.open("output.txt", std::fstream::out);
	int index_in_string = 0;
	while (file_in >> symbol) {
		int result = finder.AnalyseNewStringSymbol(following_string_synbols, index_in_string); // index or -1
		if (result >= 0) {
			file_out << result << " ";
		}
		following_string_synbols.pop_front();
		following_string_synbols.push_back(symbol);
		index_in_string++;
	}
	while (following_string_synbols.size() > 0) {
		int result = finder.AnalyseNewStringSymbol(following_string_synbols, index_in_string); // index or -1
		if (result >= 0) {
			file_out << result << " ";
		}
		following_string_synbols.pop_front();
		index_in_string++;
	}
	file_in.close();
	file_out.close();
	return 0;
}