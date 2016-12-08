#include "z-function.h"

SubstringFinder::SubstringFinder(const std::string& pattern) {
	pattern_ = pattern;
	z_function_.resize(pattern.size());
	std::fill(z_function_.begin(), z_function_.end(), 0);
	left_ = right_ = 0;
}

void SubstringFinder::InitializeZFunction() {
	for (int i = 1; i < z_function_.size(); ++i) {
		if (i <= right_) { // initial assigment for discovered segment [left_, right_]
			z_function_[i] = std::min(z_function_[i - left_], right_ - i + 1);
		}
		while (i + z_function_[i] < pattern_.size() && pattern_[z_function_[i]] == pattern_[i + z_function_[i]]) {
			// while we can extend string
			++z_function_[i];
		}
		if (i + z_function_[i] - 1 > right_) { // if we went out of segment [left_, right_]
			// we have new rightmost segment
			left_ = i;
			right_ = i + z_function_[i] - 1;
		}
	}
}

int SubstringFinder::AnalyseNewStringSymbol(const std::deque<char>& following_string_symbols, int index_in_string) {
	//now the same algorithm as InitializeZFunction(), but we analyse a new string symbol
	//and z-function for this symbol <= pattern.size()
	int i = pattern_.size() + index_in_string; // index int total string
	int current_z_function = 0;
	if (i <= right_) { // initial assigment for discovered segment [left_, right_]
		current_z_function = std::min(z_function_[i - left_], right_ - i + 1);
	}
	while (current_z_function < following_string_symbols.size() && 
		   pattern_[current_z_function] == following_string_symbols[current_z_function]) {
		// while we can extend string
		++current_z_function;
	}
	if (i + current_z_function - 1 > right_) { // if we went out of segment [left_, right_]
		// we have new rightmost segment
		left_ = i;
		right_ = i + current_z_function - 1;
	}
	if (current_z_function == pattern_.size()) {
		return index_in_string; 
	} else {
		return -1; // in this case we return invalid index
	}
}